// Copyright Epic Games, Inc. All Rights Reserved.

#include "GPUTextureShareReceiver.h"

#include "GPUTextureShare.h"

#include "Containers/Ticker.h"
#include "DynamicRHI.h"
#include "Engine/TextureRenderTarget2D.h"
#include "HAL/PlatformTime.h"
#include "Misc/ScopeLock.h"
#include "RHICommandList.h"
#include "RenderingThread.h"
#include "TextureResource.h"

#include <cctype>
#include <cerrno>
#include <cstring>
#include <string>
#include <vector>

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

THIRD_PARTY_INCLUDES_START
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11on12.h>
#include <d3d12.h>
#include <dxgi1_2.h>
#include <wrl/client.h>
THIRD_PARTY_INCLUDES_END
#endif

class FGPUTextureShareReceiverInstance
{
public:
	struct FSharedTextureFrameInfo;
	class FRenderBridgeState;

	FGPUTextureShareReceiverInstance();
	~FGPUTextureShareReceiverInstance();

	bool StartReceiver(const FString& SharedName, UTextureRenderTarget2D* InTargetRenderTarget);
	void StopReceiver();
	bool IsReceiving() const;
	FString GetLastError() const;
	void Shutdown();

private:
	bool Tick(float DeltaTime);
	bool EnsureSharedMemoryOpen();
	bool ReadSharedTextureFrameInfo(FSharedTextureFrameInfo& OutFrameInfo);
	void CloseSharedMemory();
	void SetLastError(const FString& InError, bool bLogAsWarning = true);
	void ClearLastError();

	mutable FCriticalSection StateMutex;
	mutable FCriticalSection LastErrorMutex;

	FString LastError;
	FString SharedMemoryName;
	TWeakObjectPtr<UTextureRenderTarget2D> TargetRenderTarget;
	FTSTicker::FDelegateHandle TickHandle;

	void* SharedMemoryHandle = nullptr;
	bool bIsReceiving = false;
	bool bCompatibilityModeLogged = false;

	TSharedPtr<FRenderBridgeState, ESPMode::ThreadSafe> RenderBridgeState;
};
struct FGPUTextureShareReceiverInstance::FSharedTextureFrameInfo
{
	bool bValid = false;
	bool bCompatibilityMode = false;
	uint32 Version = 0;
	uint64 SharedHandleValue = 0;
	uint32 Width = 0;
	uint32 Height = 0;
	uint32 Format = 0;
	uint64 FrameId = 0;
	uint64 Generation = 0;
};

class FGPUTextureShareReceiverInstance::FRenderBridgeState
{
public:
	void Tick_RenderThread(FRHICommandListImmediate& RHICmdList, FSharedTextureFrameInfo FrameInfo, const FTextureRHIRef& TargetTexture, FGPUTextureShareReceiverInstance* Owner);
	void Shutdown_RenderThread();

private:
#if PLATFORM_WINDOWS
	bool EnsureBridgeInitialized(FGPUTextureShareReceiverInstance* Owner);
	bool EnsureSourceTexture(FSharedTextureFrameInfo& FrameInfo, FGPUTextureShareReceiverInstance* Owner);
	bool EnsureWrappedTarget(const FTextureRHIRef& TargetTexture, FGPUTextureShareReceiverInstance* Owner);
	void InvalidateSourceTexture();
	void InvalidateWrappedTarget();

	Microsoft::WRL::ComPtr<ID3D12Device> D3D12Device;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> GraphicsQueue;
	Microsoft::WRL::ComPtr<ID3D11Device> D3D11Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> D3D11DeviceContext;
	Microsoft::WRL::ComPtr<ID3D11On12Device> D3D11On12Device;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> SourceTexture;
	Microsoft::WRL::ComPtr<IDXGIKeyedMutex> SourceKeyedMutex;
	uint64 OpenedHandle = 0;
	uint64 OpenedGeneration = 0;

	Microsoft::WRL::ComPtr<ID3D11Resource> WrappedTargetResource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> WrappedTargetTexture;
	void* WrappedTargetNativeResource = nullptr;

	bool bBridgeInitialized = false;
#endif
};

#if PLATFORM_WINDOWS
namespace
{
	constexpr uint32 SharedTextureMagic = 0x58545357u; // "WSTX"
	constexpr uint32 SharedTextureVersionMin = 1;
	constexpr DWORD KeyedMutexTimeoutMs = 2;

	struct FHeaderLayoutCandidate
	{
		const TCHAR* Name = TEXT("Unknown");
		bool bHandleIs32Bit = false;
		uint32 HandleOffset = 0;
		uint32 WidthOffset = 0;
		uint32 HeightOffset = 0;
		uint32 FormatOffset = 0;
		uint32 FrameIdOffset = 0;
		uint32 GenerationOffset = 0;
	};

	bool TryReadU32(const uint8* Buffer, size_t BufferSize, uint32 Offset, uint32& OutValue)
	{
		if (Buffer == nullptr || Offset + sizeof(uint32) > BufferSize)
		{
			return false;
		}

		FMemory::Memcpy(&OutValue, Buffer + Offset, sizeof(uint32));
		return true;
	}

	bool TryReadU64(const uint8* Buffer, size_t BufferSize, uint32 Offset, uint64& OutValue)
	{
		if (Buffer == nullptr || Offset + sizeof(uint64) > BufferSize)
		{
			return false;
		}

		FMemory::Memcpy(&OutValue, Buffer + Offset, sizeof(uint64));
		return true;
	}

	bool IsLikelyTextureDimension(uint32 Value)
	{
		return Value >= 16u && Value <= 32768u;
	}

	bool IsLikelyDXGIFormatValue(uint32 Value)
	{
		return Value > 0u && Value < 2048u;
	}

	int32 ScoreHeaderCandidate(uint64 HandleValue, uint32 Width, uint32 Height, uint32 Format, uint64 FrameId, uint64 Generation)
	{
		int32 Score = 0;
		if (HandleValue != 0)
		{
			Score += 1;
		}
		if (HandleValue > 0x1000ull)
		{
			Score += 1;
		}
		if (IsLikelyTextureDimension(Width))
		{
			Score += 3;
		}
		if (IsLikelyTextureDimension(Height))
		{
			Score += 3;
		}
		if (IsLikelyDXGIFormatValue(Format))
		{
			Score += 2;
		}
		if (FrameId != 0)
		{
			Score += 1;
		}
		if (Generation != 0)
		{
			Score += 1;
		}
		return Score;
	}

	bool TryScanDimensionsFromBuffer(const uint8* Buffer, size_t BufferSize, uint32& OutWidth, uint32& OutHeight, uint32& OutFormat)
	{
		const size_t ScanBytes = FMath::Min<size_t>(BufferSize, 128);
		int32 BestScore = INT_MIN;
		bool bFound = false;

		for (size_t Offset = 8; Offset + 12 <= ScanBytes; Offset += 4)
		{
			uint32 Width = 0;
			uint32 Height = 0;
			uint32 Format = 0;
			if (!TryReadU32(Buffer, ScanBytes, static_cast<uint32>(Offset), Width)
				|| !TryReadU32(Buffer, ScanBytes, static_cast<uint32>(Offset + 4), Height)
				|| !TryReadU32(Buffer, ScanBytes, static_cast<uint32>(Offset + 8), Format))
			{
				continue;
			}

			if (!IsLikelyTextureDimension(Width) || !IsLikelyTextureDimension(Height))
			{
				continue;
			}

			int32 Score = 5;
			if (IsLikelyDXGIFormatValue(Format))
			{
				Score += 2;
			}

			const float Aspect = static_cast<float>(Width) / static_cast<float>(FMath::Max(Height, 1u));
			if (Aspect >= 0.2f && Aspect <= 5.0f)
			{
				Score += 1;
			}

			if (Score > BestScore)
			{
				BestScore = Score;
				OutWidth = Width;
				OutHeight = Height;
				OutFormat = Format;
				bFound = true;
			}
		}

		return bFound;
	}

	bool TryParseHandleToken(const std::string& Text, uint64& OutHandle)
	{
		const char* Start = Text.c_str();
		while (*Start != '\0' && std::isspace(static_cast<unsigned char>(*Start)) != 0)
		{
			++Start;
		}

		if (*Start == '\0')
		{
			return false;
		}

		errno = 0;
		char* End = nullptr;
		const unsigned long long Parsed = std::strtoull(Start, &End, 0);
		if (Start == End || errno != 0 || Parsed == 0ull)
		{
			return false;
		}

		OutHandle = static_cast<uint64>(Parsed);
		return true;
	}

	bool TryExtractFirstHexToken(const std::string& Text, uint64& OutHandle)
	{
		const size_t HexPrefix = Text.find("0x");
		const size_t HexPrefixUpper = Text.find("0X");
		size_t TokenStart = std::string::npos;
		if (HexPrefix != std::string::npos && HexPrefixUpper != std::string::npos)
		{
			TokenStart = FMath::Min(HexPrefix, HexPrefixUpper);
		}
		else if (HexPrefix != std::string::npos)
		{
			TokenStart = HexPrefix;
		}
		else if (HexPrefixUpper != std::string::npos)
		{
			TokenStart = HexPrefixUpper;
		}

		if (TokenStart == std::string::npos)
		{
			return false;
		}

		size_t TokenEnd = TokenStart + 2;
		while (TokenEnd < Text.size() && std::isxdigit(static_cast<unsigned char>(Text[TokenEnd])) != 0)
		{
			++TokenEnd;
		}

		if (TokenEnd <= TokenStart + 2)
		{
			return false;
		}

		return TryParseHandleToken(Text.substr(TokenStart, TokenEnd - TokenStart), OutHandle);
	}

	void AddHandleCandidateUnique(std::vector<uint64>& Candidates, uint64 HandleValue)
	{
		if (HandleValue <= 0x1000ull)
		{
			return;
		}

		for (const uint64 Existing : Candidates)
		{
			if (Existing == HandleValue)
			{
				return;
			}
		}

		if (Candidates.size() < 64)
		{
			Candidates.push_back(HandleValue);
		}
	}

	std::string WideToUtf8(const wchar_t* Data, size_t MaxChars)
	{
		if (Data == nullptr || MaxChars == 0)
		{
			return std::string();
		}

		size_t CharCount = 0;
		while (CharCount < MaxChars && Data[CharCount] != L'\0')
		{
			++CharCount;
		}

		if (CharCount == 0)
		{
			return std::string();
		}

		const int RequiredSize = WideCharToMultiByte(CP_UTF8, 0, Data, static_cast<int>(CharCount), nullptr, 0, nullptr, nullptr);
		if (RequiredSize <= 0)
		{
			return std::string();
		}

		std::string Result(static_cast<size_t>(RequiredSize), '\0');
		const int Converted = WideCharToMultiByte(CP_UTF8, 0, Data, static_cast<int>(CharCount), Result.data(), RequiredSize, nullptr, nullptr);
		if (Converted <= 0)
		{
			return std::string();
		}

		return Result;
	}

	void ExtractHexTokensFromBuffer(const uint8* Buffer, size_t BufferSize, std::vector<uint64>& OutCandidates)
	{
		if (Buffer == nullptr || BufferSize < 3)
		{
			return;
		}

		for (size_t Index = 0; Index + 2 < BufferSize; ++Index)
		{
			if (Buffer[Index] != '0')
			{
				continue;
			}

			const uint8 Marker = Buffer[Index + 1];
			if (Marker != 'x' && Marker != 'X')
			{
				continue;
			}

			size_t End = Index + 2;
			while (End < BufferSize && std::isxdigit(Buffer[End]) != 0)
			{
				++End;
			}

			if (End <= Index + 2)
			{
				continue;
			}

			const std::string Token(reinterpret_cast<const char*>(Buffer + Index), End - Index);
			uint64 Handle = 0;
			if (TryParseHandleToken(Token, Handle))
			{
				AddHandleCandidateUnique(OutCandidates, Handle);
			}
		}
	}

	bool TryParseFixedHeader(const uint8* Buffer, size_t BufferSize, FGPUTextureShareReceiverInstance::FSharedTextureFrameInfo& OutInfo)
	{
		if (Buffer == nullptr || BufferSize < 12)
		{
			return false;
		}

		uint32 Magic = 0;
		uint32 Version = 0;
		if (!TryReadU32(Buffer, BufferSize, 0, Magic)
			|| !TryReadU32(Buffer, BufferSize, 4, Version)
			|| Magic != SharedTextureMagic
			|| Version < SharedTextureVersionMin)
		{
			return false;
		}

		static const FHeaderLayoutCandidate Layouts[] =
		{
			{ TEXT("V1Packed"), false, 8, 16, 20, 24, 28, 36 },
			{ TEXT("V1Aligned"), false, 8, 16, 20, 24, 32, 40 },
			{ TEXT("V1MetaFirst"), false, 8, 32, 36, 40, 16, 24 },
			{ TEXT("V1Handle32Packed"), true, 8, 12, 16, 20, 24, 32 },
			{ TEXT("V1Handle32Aligned"), true, 8, 16, 20, 24, 28, 36 },
			{ TEXT("V1HandleAt32"), true, 32, 40, 44, 48, 24, 56 },
		};

		bool bFoundCandidate = false;
		int32 BestScore = INT_MIN;
		FGPUTextureShareReceiverInstance::FSharedTextureFrameInfo BestInfo = {};

		for (const FHeaderLayoutCandidate& Layout : Layouts)
		{
			uint64 HandleValue = 0;
			if (Layout.bHandleIs32Bit)
			{
				uint32 Handle32 = 0;
				if (!TryReadU32(Buffer, BufferSize, Layout.HandleOffset, Handle32))
				{
					continue;
				}
				HandleValue = static_cast<uint64>(Handle32);
			}
			else
			{
				if (!TryReadU64(Buffer, BufferSize, Layout.HandleOffset, HandleValue))
				{
					continue;
				}
			}

			if (HandleValue == 0)
			{
				continue;
			}

			uint32 Width = 0;
			uint32 Height = 0;
			uint32 Format = 0;
			uint64 FrameId = 0;
			uint64 Generation = 0;
			TryReadU32(Buffer, BufferSize, Layout.WidthOffset, Width);
			TryReadU32(Buffer, BufferSize, Layout.HeightOffset, Height);
			TryReadU32(Buffer, BufferSize, Layout.FormatOffset, Format);
			TryReadU64(Buffer, BufferSize, Layout.FrameIdOffset, FrameId);
			TryReadU64(Buffer, BufferSize, Layout.GenerationOffset, Generation);

			FGPUTextureShareReceiverInstance::FSharedTextureFrameInfo ParsedInfo = {};
			ParsedInfo.bValid = true;
			ParsedInfo.bCompatibilityMode = false;
			ParsedInfo.Version = Version;
			ParsedInfo.SharedHandleValue = HandleValue;
			ParsedInfo.Width = Width;
			ParsedInfo.Height = Height;
			ParsedInfo.Format = Format;
			ParsedInfo.FrameId = FrameId;
			ParsedInfo.Generation = Generation;

			const int32 Score = ScoreHeaderCandidate(HandleValue, Width, Height, Format, FrameId, Generation);
			if (Score > BestScore)
			{
				BestScore = Score;
				BestInfo = ParsedInfo;
				bFoundCandidate = true;
			}
		}

		if (!bFoundCandidate)
		{
			return false;
		}

		if (!IsLikelyTextureDimension(BestInfo.Width) || !IsLikelyTextureDimension(BestInfo.Height))
		{
			uint32 ScannedWidth = 0;
			uint32 ScannedHeight = 0;
			uint32 ScannedFormat = 0;
			if (TryScanDimensionsFromBuffer(Buffer, BufferSize, ScannedWidth, ScannedHeight, ScannedFormat))
			{
				BestInfo.Width = ScannedWidth;
				BestInfo.Height = ScannedHeight;
				if (!IsLikelyDXGIFormatValue(BestInfo.Format) && IsLikelyDXGIFormatValue(ScannedFormat))
				{
					BestInfo.Format = ScannedFormat;
				}
			}
		}

		if (!IsLikelyTextureDimension(BestInfo.Width) || !IsLikelyTextureDimension(BestInfo.Height))
		{
			return false;
		}

		OutInfo = BestInfo;
		return true;
	}

	bool TryParseLegacyHandle(const uint8* Buffer, size_t BufferSize, FGPUTextureShareReceiverInstance::FSharedTextureFrameInfo& OutInfo)
	{
		if (Buffer == nullptr || BufferSize == 0)
		{
			return false;
		}

		std::vector<uint64> Candidates;
		if (BufferSize >= 16)
		{
			uint32 LegacyMagic = 0;
			FMemory::Memcpy(&LegacyMagic, Buffer, sizeof(uint32));
			if (LegacyMagic == SharedTextureMagic)
			{
				uint64 HandleAtOffset8 = 0;
				uint32 HandleAtOffset8_32 = 0;
				FMemory::Memcpy(&HandleAtOffset8, Buffer + 8, sizeof(uint64));
				FMemory::Memcpy(&HandleAtOffset8_32, Buffer + 8, sizeof(uint32));
				AddHandleCandidateUnique(Candidates, HandleAtOffset8);
				AddHandleCandidateUnique(Candidates, static_cast<uint64>(HandleAtOffset8_32));

				uint32 HandleAtOffset32_32 = 0;
				if (TryReadU32(Buffer, BufferSize, 32, HandleAtOffset32_32))
				{
					AddHandleCandidateUnique(Candidates, static_cast<uint64>(HandleAtOffset32_32));
				}

				uint64 HandleAtOffset32_64 = 0;
				if (TryReadU64(Buffer, BufferSize, 32, HandleAtOffset32_64))
				{
					AddHandleCandidateUnique(Candidates, HandleAtOffset32_64);
				}
			}
		}

		const size_t ScanBytes = FMath::Min<size_t>(BufferSize, 4096);
		const size_t AsciiLength = strnlen_s(reinterpret_cast<const char*>(Buffer), ScanBytes);
		if (AsciiLength > 0)
		{
			const std::string AsciiText(reinterpret_cast<const char*>(Buffer), AsciiLength);
			uint64 Parsed = 0;
			if (TryParseHandleToken(AsciiText, Parsed) || TryExtractFirstHexToken(AsciiText, Parsed))
			{
				AddHandleCandidateUnique(Candidates, Parsed);
			}
		}

		const size_t MaxWideChars = FMath::Min<size_t>(ScanBytes / sizeof(wchar_t), 512);
		if (MaxWideChars > 0)
		{
			const std::string Utf8Text = WideToUtf8(reinterpret_cast<const wchar_t*>(Buffer), MaxWideChars);
			if (!Utf8Text.empty())
			{
				uint64 Parsed = 0;
				if (TryParseHandleToken(Utf8Text, Parsed) || TryExtractFirstHexToken(Utf8Text, Parsed))
				{
					AddHandleCandidateUnique(Candidates, Parsed);
				}
			}
		}

		ExtractHexTokensFromBuffer(Buffer, ScanBytes, Candidates);

		const size_t BinaryScanBytes = FMath::Min<size_t>(ScanBytes, 512);
		for (size_t Offset = 0; Offset + sizeof(uint64) <= BinaryScanBytes; Offset += 4)
		{
			uint64 Value = 0;
			FMemory::Memcpy(&Value, Buffer + Offset, sizeof(uint64));
			AddHandleCandidateUnique(Candidates, Value);
		}
		for (size_t Offset = 0; Offset + sizeof(uint32) <= BinaryScanBytes; Offset += 4)
		{
			uint32 Value = 0;
			FMemory::Memcpy(&Value, Buffer + Offset, sizeof(uint32));
			AddHandleCandidateUnique(Candidates, static_cast<uint64>(Value));
		}

		if (Candidates.empty())
		{
			return false;
		}

		auto ScoreLegacyHandle = [](uint64 HandleValue) -> int32
		{
			int32 Score = 0;
			if (HandleValue > 0x1000ull)
			{
				Score += 1;
			}

			const uint32 High32 = static_cast<uint32>(HandleValue >> 32);
			const uint32 Low32 = static_cast<uint32>(HandleValue & 0xFFFFFFFFull);
			if (High32 == 0)
			{
				Score += 2;
			}
			if (Low32 > 0x1000u)
			{
				Score += 1;
			}
			if (High32 > 0 && Low32 <= 0x1000u)
			{
				Score -= 3;
			}
			return Score;
		};

		uint64 BestHandle = Candidates[0];
		int32 BestHandleScore = ScoreLegacyHandle(BestHandle);
		for (const uint64 Candidate : Candidates)
		{
			const int32 CandidateScore = ScoreLegacyHandle(Candidate);
			if (CandidateScore > BestHandleScore)
			{
				BestHandle = Candidate;
				BestHandleScore = CandidateScore;
			}
		}

		uint32 ScannedWidth = 0;
		uint32 ScannedHeight = 0;
		uint32 ScannedFormat = 0;
		const bool bHasScannedDimensions = TryScanDimensionsFromBuffer(Buffer, ScanBytes, ScannedWidth, ScannedHeight, ScannedFormat);

		OutInfo.bValid = true;
		OutInfo.bCompatibilityMode = true;
		OutInfo.Version = 0;
		OutInfo.SharedHandleValue = BestHandle;
		OutInfo.Width = bHasScannedDimensions ? ScannedWidth : 0;
		OutInfo.Height = bHasScannedDimensions ? ScannedHeight : 0;
		OutInfo.Format = (bHasScannedDimensions && IsLikelyDXGIFormatValue(ScannedFormat)) ? ScannedFormat : 0;
		OutInfo.FrameId = 0;
		OutInfo.Generation = 0;
		return true;
	}

	FString HResultToString(HRESULT Hr)
	{
		return FString::Printf(TEXT("0x%08x"), static_cast<uint32>(Hr));
	}
}
#endif

FGPUTextureShareReceiverInstance::FGPUTextureShareReceiverInstance()
{
}

FGPUTextureShareReceiverInstance::~FGPUTextureShareReceiverInstance()
{
	Shutdown();
}

bool FGPUTextureShareReceiverInstance::StartReceiver(const FString& SharedName, UTextureRenderTarget2D* InTargetRenderTarget)
{
	const FString TrimmedSharedName = SharedName.TrimStartAndEnd();
	if (TrimmedSharedName.IsEmpty())
	{
		SetLastError(TEXT("StartReceiver failed: shared mapping name is empty."));
		return false;
	}

	if (InTargetRenderTarget == nullptr)
	{
		SetLastError(TEXT("StartReceiver failed: target UTextureRenderTarget2D is null."));
		return false;
	}

#if !PLATFORM_WINDOWS
	SetLastError(TEXT("StartReceiver is only supported on Windows."));
	return false;
#else
	if (GDynamicRHI == nullptr)
	{
		SetLastError(TEXT("StartReceiver failed: RHI is not initialized."));
		return false;
	}

	const FString RHIName = GDynamicRHI->GetName();
	if (!RHIName.Contains(TEXT("D3D12"), ESearchCase::IgnoreCase))
	{
		SetLastError(FString::Printf(TEXT("StartReceiver failed: current RHI is '%s', only D3D12 is supported."), *RHIName));
		return false;
	}

	StopReceiver();

	{
		FScopeLock StateLock(&StateMutex);
		SharedMemoryName = TrimmedSharedName;
		TargetRenderTarget = InTargetRenderTarget;
		bIsReceiving = true;
		bCompatibilityModeLogged = false;
		RenderBridgeState = MakeShared<FRenderBridgeState, ESPMode::ThreadSafe>();
	}

	ClearLastError();

	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FGPUTextureShareReceiverInstance::Tick));
	UE_LOG(LogGPUTextureShare, Log, TEXT("Receiver started. Mapping='%s', Target='%s'"), *TrimmedSharedName, *GetNameSafe(InTargetRenderTarget));
	return true;
#endif
}

void FGPUTextureShareReceiverInstance::StopReceiver()
{
	TSharedPtr<FRenderBridgeState, ESPMode::ThreadSafe> RenderStateToShutdown;
	bool bWasActive = false;

	{
		FScopeLock StateLock(&StateMutex);
		bWasActive = bIsReceiving || SharedMemoryHandle != nullptr || RenderBridgeState.IsValid() || TickHandle.IsValid();
		bIsReceiving = false;
		TargetRenderTarget.Reset();
		SharedMemoryName.Reset();
		bCompatibilityModeLogged = false;
		RenderStateToShutdown = MoveTemp(RenderBridgeState);
	}

	if (!bWasActive)
	{
		return;
	}

	if (TickHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
		TickHandle.Reset();
	}

	CloseSharedMemory();

	if (RenderStateToShutdown.IsValid())
	{
		if (IsInRenderingThread())
		{
			RenderStateToShutdown->Shutdown_RenderThread();
		}
		else
		{
			ENQUEUE_RENDER_COMMAND(GPUTextureShare_StopReceiver)(
				[RenderStateToShutdown](FRHICommandListImmediate& RHICmdList)
				{
					RenderStateToShutdown->Shutdown_RenderThread();
				});

			FlushRenderingCommands();
		}
	}

	UE_LOG(LogGPUTextureShare, Log, TEXT("Receiver stopped."));
}

bool FGPUTextureShareReceiverInstance::IsReceiving() const
{
	FScopeLock StateLock(&StateMutex);
	return bIsReceiving;
}

FString FGPUTextureShareReceiverInstance::GetLastError() const
{
	FScopeLock ErrorLock(&LastErrorMutex);
	return LastError;
}

void FGPUTextureShareReceiverInstance::Shutdown()
{
	StopReceiver();
}

bool FGPUTextureShareReceiverInstance::Tick(float DeltaTime)
{
	(void)DeltaTime;

	TWeakObjectPtr<UTextureRenderTarget2D> TargetToUse;
	TSharedPtr<FRenderBridgeState, ESPMode::ThreadSafe> RenderState;
	{
		FScopeLock StateLock(&StateMutex);
		if (!bIsReceiving)
		{
			return false;
		}

		TargetToUse = TargetRenderTarget;
		RenderState = RenderBridgeState;
	}

	if (!TargetToUse.IsValid())
	{
		SetLastError(TEXT("Receiver stopped: target UTextureRenderTarget2D is no longer valid."));
		StopReceiver();
		return false;
	}

	FSharedTextureFrameInfo FrameInfo;
	if (!ReadSharedTextureFrameInfo(FrameInfo))
	{
		return true;
	}

	if (!FrameInfo.bValid || !RenderState.IsValid())
	{
		return true;
	}

	FTextureRenderTargetResource* RenderTargetResource = TargetToUse->GameThread_GetRenderTargetResource();
	if (RenderTargetResource == nullptr)
	{
		return true;
	}

	const FTextureRHIRef TargetTexture = RenderTargetResource->GetRenderTargetTexture();
	if (!TargetTexture.IsValid())
	{
		return true;
	}

	ENQUEUE_RENDER_COMMAND(GPUTextureShare_CopyFrame)(
		[RenderState, FrameInfo, TargetTexture, this](FRHICommandListImmediate& RHICmdList)
		{
			RenderState->Tick_RenderThread(RHICmdList, FrameInfo, TargetTexture, this);
		});

	return true;
}

bool FGPUTextureShareReceiverInstance::EnsureSharedMemoryOpen()
{
#if !PLATFORM_WINDOWS
	return false;
#else
	FString MappingName;
	{
		FScopeLock StateLock(&StateMutex);
		if (SharedMemoryHandle != nullptr)
		{
			return true;
		}

		MappingName = SharedMemoryName;
	}

	if (MappingName.IsEmpty())
	{
		SetLastError(TEXT("Shared memory name is empty."));
		return false;
	}

	HANDLE NewMappingHandle = OpenFileMappingW(FILE_MAP_READ, 0, *MappingName);
	if (NewMappingHandle == nullptr)
	{
		SetLastError(FString::Printf(TEXT("OpenFileMappingW('%s') failed. WinErr=%u"), *MappingName, ::GetLastError()), false);
		return false;
	}

	{
		FScopeLock StateLock(&StateMutex);
		if (SharedMemoryHandle == nullptr)
		{
			SharedMemoryHandle = NewMappingHandle;
		}
		else
		{
			CloseHandle(NewMappingHandle);
		}
	}

	return true;
#endif
}

bool FGPUTextureShareReceiverInstance::ReadSharedTextureFrameInfo(FSharedTextureFrameInfo& OutFrameInfo)
{
#if !PLATFORM_WINDOWS
	OutFrameInfo = FSharedTextureFrameInfo();
	return false;
#else
	OutFrameInfo = FSharedTextureFrameInfo();
	if (!EnsureSharedMemoryOpen())
	{
		return false;
	}

	HANDLE MappingHandle = nullptr;
	{
		FScopeLock StateLock(&StateMutex);
		MappingHandle = static_cast<HANDLE>(SharedMemoryHandle);
	}

	if (MappingHandle == nullptr)
	{
		return false;
	}

	void* MappedView = MapViewOfFile(MappingHandle, FILE_MAP_READ, 0, 0, 0);
	if (MappedView == nullptr)
	{
		SetLastError(FString::Printf(TEXT("MapViewOfFile failed. WinErr=%u"), ::GetLastError()), false);
		CloseSharedMemory();
		return false;
	}

	MEMORY_BASIC_INFORMATION MemoryInfo = {};
	if (VirtualQuery(MappedView, &MemoryInfo, sizeof(MemoryInfo)) == 0)
	{
		SetLastError(FString::Printf(TEXT("VirtualQuery failed. WinErr=%u"), ::GetLastError()), false);
		UnmapViewOfFile(MappedView);
		return false;
	}

	const size_t ScanBytes = FMath::Min<size_t>(MemoryInfo.RegionSize, 4096);
	const uint8* Buffer = static_cast<const uint8*>(MappedView);
	const bool bParsedFixedHeader = TryParseFixedHeader(Buffer, ScanBytes, OutFrameInfo);
	bool bParsedLegacy = false;
	if (!bParsedFixedHeader)
	{
		bParsedLegacy = TryParseLegacyHandle(Buffer, ScanBytes, OutFrameInfo);
	}

	UnmapViewOfFile(MappedView);

	if (!OutFrameInfo.bValid)
	{
		SetLastError(TEXT("Shared memory parse failed: no valid texture handle found."), false);
		return false;
	}

	if (bParsedLegacy)
	{
		bool bNeedLogCompatibility = false;
		{
			FScopeLock StateLock(&StateMutex);
			if (!bCompatibilityModeLogged)
			{
				bCompatibilityModeLogged = true;
				bNeedLogCompatibility = true;
			}
		}

		if (bNeedLogCompatibility)
		{
			UE_LOG(LogGPUTextureShare, Warning, TEXT("Shared memory parser switched to compatibility mode for mapping '%s'."), *SharedMemoryName);
		}
	}

	return true;
#endif
}

void FGPUTextureShareReceiverInstance::CloseSharedMemory()
{
#if PLATFORM_WINDOWS
	HANDLE MappingHandleToClose = nullptr;
	{
		FScopeLock StateLock(&StateMutex);
		MappingHandleToClose = static_cast<HANDLE>(SharedMemoryHandle);
		SharedMemoryHandle = nullptr;
	}

	if (MappingHandleToClose != nullptr)
	{
		CloseHandle(MappingHandleToClose);
	}
#else
	FScopeLock StateLock(&StateMutex);
	SharedMemoryHandle = nullptr;
#endif
}

void FGPUTextureShareReceiverInstance::SetLastError(const FString& InError, bool bLogAsWarning)
{
	if (InError.IsEmpty())
	{
		return;
	}

	bool bHasChanged = false;
	{
		FScopeLock ErrorLock(&LastErrorMutex);
		if (LastError != InError)
		{
			LastError = InError;
			bHasChanged = true;
		}
	}

	if (bHasChanged && bLogAsWarning)
	{
		UE_LOG(LogGPUTextureShare, Warning, TEXT("%s"), *InError);
	}
}

void FGPUTextureShareReceiverInstance::ClearLastError()
{
	FScopeLock ErrorLock(&LastErrorMutex);
	LastError.Reset();
}

void FGPUTextureShareReceiverInstance::FRenderBridgeState::Tick_RenderThread(FRHICommandListImmediate& RHICmdList, FSharedTextureFrameInfo FrameInfo, const FTextureRHIRef& TargetTexture, FGPUTextureShareReceiverInstance* Owner)
{
#if !PLATFORM_WINDOWS
	(void)RHICmdList;
	(void)FrameInfo;
	(void)TargetTexture;
	(void)Owner;
#else
	if (!TargetTexture.IsValid() || Owner == nullptr || !FrameInfo.bValid || FrameInfo.SharedHandleValue == 0)
	{
		return;
	}

	if (!EnsureBridgeInitialized(Owner))
	{
		return;
	}

	if (!EnsureSourceTexture(FrameInfo, Owner))
	{
		return;
	}

	if (!EnsureWrappedTarget(TargetTexture, Owner))
	{
		return;
	}

	bool bMutexAcquired = false;
	if (SourceKeyedMutex)
	{
		const HRESULT MutexHr = SourceKeyedMutex->AcquireSync(0, KeyedMutexTimeoutMs);
		if (MutexHr == DXGI_ERROR_WAIT_TIMEOUT || MutexHr == HRESULT_FROM_WIN32(WAIT_TIMEOUT))
		{
			UE_LOG(LogGPUTextureShare, Verbose, TEXT("Keyed mutex timeout. Frame skipped."));
			return;
		}

		if (FAILED(MutexHr))
		{
			Owner->SetLastError(FString::Printf(TEXT("Keyed mutex acquire failed: %s"), *HResultToString(MutexHr)), false);
			InvalidateSourceTexture();
			return;
		}

		bMutexAcquired = true;
	}

	FRHITexture* TargetTextureRHI = TargetTexture.GetReference();
	RHICmdList.Transition(FRHITransitionInfo(TargetTextureRHI, ERHIAccess::Unknown, ERHIAccess::CopyDest));

	ID3D11Resource* WrappedResources[] = { WrappedTargetResource.Get() };
	D3D11On12Device->AcquireWrappedResources(WrappedResources, UE_ARRAY_COUNT(WrappedResources));

	D3D11_TEXTURE2D_DESC SourceDesc = {};
	D3D11_TEXTURE2D_DESC DestDesc = {};
	SourceTexture->GetDesc(&SourceDesc);
	WrappedTargetTexture->GetDesc(&DestDesc);

	const UINT CopyWidth = FMath::Min(SourceDesc.Width, DestDesc.Width);
	const UINT CopyHeight = FMath::Min(SourceDesc.Height, DestDesc.Height);
	if (CopyWidth > 0 && CopyHeight > 0)
	{
		if (CopyWidth == SourceDesc.Width && CopyHeight == SourceDesc.Height && SourceDesc.Width == DestDesc.Width && SourceDesc.Height == DestDesc.Height)
		{
			D3D11DeviceContext->CopyResource(WrappedTargetTexture.Get(), SourceTexture.Get());
		}
		else
		{
			D3D11_BOX CopyBox = {};
			CopyBox.left = 0;
			CopyBox.top = 0;
			CopyBox.front = 0;
			CopyBox.right = CopyWidth;
			CopyBox.bottom = CopyHeight;
			CopyBox.back = 1;
			D3D11DeviceContext->CopySubresourceRegion(WrappedTargetTexture.Get(), 0, 0, 0, 0, SourceTexture.Get(), 0, &CopyBox);
		}
	}

	D3D11On12Device->ReleaseWrappedResources(WrappedResources, UE_ARRAY_COUNT(WrappedResources));
	D3D11DeviceContext->Flush();

	if (bMutexAcquired)
	{
		SourceKeyedMutex->ReleaseSync(0);
	}

	RHICmdList.Transition(FRHITransitionInfo(TargetTextureRHI, ERHIAccess::CopyDest, ERHIAccess::SRVMask));
	Owner->ClearLastError();
#endif
}

void FGPUTextureShareReceiverInstance::FRenderBridgeState::Shutdown_RenderThread()
{
#if PLATFORM_WINDOWS
	InvalidateSourceTexture();
	InvalidateWrappedTarget();
	D3D11On12Device.Reset();
	D3D11DeviceContext.Reset();
	D3D11Device.Reset();
	GraphicsQueue.Reset();
	D3D12Device.Reset();
	bBridgeInitialized = false;
#endif
}

#if PLATFORM_WINDOWS
bool FGPUTextureShareReceiverInstance::FRenderBridgeState::EnsureBridgeInitialized(FGPUTextureShareReceiverInstance* Owner)
{
	if (bBridgeInitialized)
	{
		return true;
	}

	ID3D12Device* NativeDevice = static_cast<ID3D12Device*>(RHIGetNativeDevice());
	ID3D12CommandQueue* NativeGraphicsQueue = static_cast<ID3D12CommandQueue*>(RHIGetNativeGraphicsQueue());
	if (NativeDevice == nullptr || NativeGraphicsQueue == nullptr)
	{
		Owner->SetLastError(TEXT("D3D11On12 init failed: native D3D12 device or queue is null."));
		return false;
	}

	D3D12Device = NativeDevice;
	GraphicsQueue = NativeGraphicsQueue;

	IUnknown* Queues[] = { GraphicsQueue.Get() };
	UINT DeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	HRESULT Hr = D3D11On12CreateDevice(
		D3D12Device.Get(),
		DeviceFlags,
		nullptr,
		0,
		Queues,
		UE_ARRAY_COUNT(Queues),
		0,
		D3D11Device.GetAddressOf(),
		D3D11DeviceContext.GetAddressOf(),
		nullptr);

	if (FAILED(Hr))
	{
		Owner->SetLastError(FString::Printf(TEXT("D3D11On12CreateDevice failed: %s"), *HResultToString(Hr)));
		return false;
	}

	Hr = D3D11Device.As(&D3D11On12Device);
	if (FAILED(Hr) || !D3D11On12Device)
	{
		Owner->SetLastError(FString::Printf(TEXT("ID3D11On12Device query failed: %s"), *HResultToString(Hr)));
		return false;
	}

	bBridgeInitialized = true;
	UE_LOG(LogGPUTextureShare, Log, TEXT("D3D11On12 bridge initialized."));
	return true;
}

bool FGPUTextureShareReceiverInstance::FRenderBridgeState::EnsureSourceTexture(FSharedTextureFrameInfo& FrameInfo, FGPUTextureShareReceiverInstance* Owner)
{
	if (FrameInfo.SharedHandleValue == 0)
	{
		InvalidateSourceTexture();
		return false;
	}

	const bool bHandleChanged = (SourceTexture == nullptr) || (OpenedHandle != FrameInfo.SharedHandleValue);
	const bool bGenerationChanged = (FrameInfo.Generation != 0 && OpenedGeneration != 0 && OpenedGeneration != FrameInfo.Generation);
	if (bHandleChanged || bGenerationChanged)
	{
		InvalidateSourceTexture();
	}

	if (SourceTexture)
	{
		return true;
	}

	const HANDLE SharedHandle = reinterpret_cast<HANDLE>(static_cast<uintptr_t>(FrameInfo.SharedHandleValue));

	HRESULT Hr = E_FAIL;
	Microsoft::WRL::ComPtr<ID3D11Device1> D3D11Device1;
	if (SUCCEEDED(D3D11Device.As(&D3D11Device1)) && D3D11Device1)
	{
		Hr = D3D11Device1->OpenSharedResource1(SharedHandle, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(SourceTexture.GetAddressOf()));
	}

	if (FAILED(Hr))
	{
		SourceTexture.Reset();
		Hr = D3D11Device->OpenSharedResource(SharedHandle, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(SourceTexture.GetAddressOf()));
	}

	if (FAILED(Hr) || !SourceTexture)
	{
		Owner->SetLastError(FString::Printf(TEXT("OpenSharedResource failed for handle=0x%llx, hr=%s"), FrameInfo.SharedHandleValue, *HResultToString(Hr)), false);
		InvalidateSourceTexture();
		return false;
	}

	SourceKeyedMutex.Reset();
	SourceTexture.As(&SourceKeyedMutex);
	OpenedHandle = FrameInfo.SharedHandleValue;
	OpenedGeneration = FrameInfo.Generation;

	D3D11_TEXTURE2D_DESC SourceDesc = {};
	SourceTexture->GetDesc(&SourceDesc);
	if (FrameInfo.Width == 0 || FrameInfo.Height == 0)
	{
		FrameInfo.Width = SourceDesc.Width;
		FrameInfo.Height = SourceDesc.Height;
	}
	if (FrameInfo.Format == 0)
	{
		FrameInfo.Format = static_cast<uint32>(SourceDesc.Format);
	}

	if (FrameInfo.Width > 0 && FrameInfo.Height > 0 && (SourceDesc.Width != FrameInfo.Width || SourceDesc.Height != FrameInfo.Height))
	{
		UE_LOG(LogGPUTextureShare, Warning, TEXT("Shared texture dimensions mismatch. Header=%ux%u, Resource=%ux%u"), FrameInfo.Width, FrameInfo.Height, SourceDesc.Width, SourceDesc.Height);
	}
	if (FrameInfo.Format != 0 && SourceDesc.Format != static_cast<DXGI_FORMAT>(FrameInfo.Format))
	{
		UE_LOG(LogGPUTextureShare, Warning, TEXT("Shared texture format mismatch. Header=%u, Resource=%u"), FrameInfo.Format, static_cast<uint32>(SourceDesc.Format));
	}

	UE_LOG(LogGPUTextureShare, Verbose, TEXT("Shared texture opened. Handle=0x%llx, Size=%ux%u, Format=%u, KeyedMutex=%s"),
		OpenedHandle,
		SourceDesc.Width,
		SourceDesc.Height,
		static_cast<uint32>(SourceDesc.Format),
		SourceKeyedMutex ? TEXT("Yes") : TEXT("No"));
	return true;
}

bool FGPUTextureShareReceiverInstance::FRenderBridgeState::EnsureWrappedTarget(const FTextureRHIRef& TargetTexture, FGPUTextureShareReceiverInstance* Owner)
{
	FRHITexture* TargetTextureRHI = TargetTexture.GetReference();
	if (TargetTextureRHI == nullptr)
	{
		return false;
	}

	void* NativeResource = TargetTextureRHI->GetNativeResource();
	if (NativeResource == nullptr)
	{
		Owner->SetLastError(TEXT("Target render target native resource is null."), false);
		return false;
	}

	if (WrappedTargetResource && WrappedTargetTexture && WrappedTargetNativeResource == NativeResource)
	{
		return true;
	}

	InvalidateWrappedTarget();

	D3D11_RESOURCE_FLAGS ResourceFlags = {};
	HRESULT Hr = D3D11On12Device->CreateWrappedResource(
		reinterpret_cast<IUnknown*>(NativeResource),
		&ResourceFlags,
		D3D12_RESOURCE_STATE_COPY_DEST,
		D3D12_RESOURCE_STATE_COPY_DEST,
		__uuidof(ID3D11Resource),
		reinterpret_cast<void**>(WrappedTargetResource.GetAddressOf()));

	if (FAILED(Hr) || !WrappedTargetResource)
	{
		Owner->SetLastError(FString::Printf(TEXT("CreateWrappedResource failed: %s"), *HResultToString(Hr)), false);
		return false;
	}

	Hr = WrappedTargetResource.As(&WrappedTargetTexture);
	if (FAILED(Hr) || !WrappedTargetTexture)
	{
		Owner->SetLastError(FString::Printf(TEXT("Wrapped target is not ID3D11Texture2D: %s"), *HResultToString(Hr)), false);
		InvalidateWrappedTarget();
		return false;
	}

	WrappedTargetNativeResource = NativeResource;
	return true;
}

void FGPUTextureShareReceiverInstance::FRenderBridgeState::InvalidateSourceTexture()
{
	SourceKeyedMutex.Reset();
	SourceTexture.Reset();
	OpenedHandle = 0;
	OpenedGeneration = 0;
}

void FGPUTextureShareReceiverInstance::FRenderBridgeState::InvalidateWrappedTarget()
{
	WrappedTargetTexture.Reset();
	WrappedTargetResource.Reset();
	WrappedTargetNativeResource = nullptr;
}
#endif

FGPUTextureShareReceiver::FGPUTextureShareReceiver()
{
}

FGPUTextureShareReceiver::~FGPUTextureShareReceiver()
{
	Shutdown();
}

bool FGPUTextureShareReceiver::StartReceiver(const FString& SharedName, UTextureRenderTarget2D* InTargetRenderTarget)
{
	const FString NormalizedName = NormalizeSharedName(SharedName);
	if (NormalizedName.IsEmpty())
	{
		SetLastError(TEXT("StartReceiver failed: shared mapping name is empty."));
		return false;
	}

	TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe> ReceiverInstance;
	bool bCreated = false;
	{
		FScopeLock Lock(&ManagerMutex);
		PruneStoppedReceivers_NoLock();

		if (TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>* Found = ReceiverInstances.Find(NormalizedName))
		{
			ReceiverInstance = *Found;
		}
		else
		{
			ReceiverInstance = MakeShared<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>();
			ReceiverInstances.Add(NormalizedName, ReceiverInstance);
			bCreated = true;
		}
	}

	if (!ReceiverInstance.IsValid() || !ReceiverInstance->StartReceiver(NormalizedName, InTargetRenderTarget))
	{
		const FString InstanceError = ReceiverInstance.IsValid() ? ReceiverInstance->GetLastError() : TEXT("Receiver instance is invalid.");
		SetLastError(FString::Printf(TEXT("StartReceiver('%s') failed: %s"), *NormalizedName, *InstanceError));

		if (bCreated)
		{
			FScopeLock Lock(&ManagerMutex);
			if (TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>* Found = ReceiverInstances.Find(NormalizedName))
			{
				if (Found->Get() == ReceiverInstance.Get() && (!ReceiverInstance.IsValid() || !ReceiverInstance->IsReceiving()))
				{
					ReceiverInstances.Remove(NormalizedName);
				}
			}
		}

		return false;
	}

	ClearLastError();
	return true;
}

bool FGPUTextureShareReceiver::StopReceiverByName(const FString& SharedName)
{
	const FString NormalizedName = NormalizeSharedName(SharedName);
	if (NormalizedName.IsEmpty())
	{
		return false;
	}

	TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe> ReceiverInstance;
	{
		FScopeLock Lock(&ManagerMutex);
		if (TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>* Found = ReceiverInstances.Find(NormalizedName))
		{
			ReceiverInstance = *Found;
			ReceiverInstances.Remove(NormalizedName);
		}
	}

	if (!ReceiverInstance.IsValid())
	{
		return false;
	}

	ReceiverInstance->StopReceiver();
	return true;
}

void FGPUTextureShareReceiver::StopReceiver()
{
	TMap<FString, TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>> InstancesToStop;
	{
		FScopeLock Lock(&ManagerMutex);
		InstancesToStop = MoveTemp(ReceiverInstances);
	}

	for (TPair<FString, TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>>& Entry : InstancesToStop)
	{
		if (Entry.Value.IsValid())
		{
			Entry.Value->StopReceiver();
		}
	}
}

bool FGPUTextureShareReceiver::IsReceivingByName(const FString& SharedName) const
{
	const FString NormalizedName = NormalizeSharedName(SharedName);
	if (NormalizedName.IsEmpty())
	{
		return false;
	}

	TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe> ReceiverInstance;
	{
		FScopeLock Lock(&ManagerMutex);
		if (const TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>* Found = ReceiverInstances.Find(NormalizedName))
		{
			ReceiverInstance = *Found;
		}
	}

	return ReceiverInstance.IsValid() && ReceiverInstance->IsReceiving();
}

bool FGPUTextureShareReceiver::IsReceiving() const
{
	FScopeLock Lock(&ManagerMutex);
	for (const TPair<FString, TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>>& Entry : ReceiverInstances)
	{
		if (Entry.Value.IsValid() && Entry.Value->IsReceiving())
		{
			return true;
		}
	}

	return false;
}

FString FGPUTextureShareReceiver::GetLastErrorByName(const FString& SharedName) const
{
	const FString NormalizedName = NormalizeSharedName(SharedName);
	if (NormalizedName.IsEmpty())
	{
		return TEXT("Shared mapping name is empty.");
	}

	TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe> ReceiverInstance;
	{
		FScopeLock Lock(&ManagerMutex);
		if (const TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>* Found = ReceiverInstances.Find(NormalizedName))
		{
			ReceiverInstance = *Found;
		}
	}

	if (!ReceiverInstance.IsValid())
	{
		return FString::Printf(TEXT("Receiver '%s' does not exist."), *NormalizedName);
	}

	return ReceiverInstance->GetLastError();
}

TArray<FString> FGPUTextureShareReceiver::GetActiveReceiverNames() const
{
	TArray<FString> ActiveNames;
	FScopeLock Lock(&ManagerMutex);
	for (const TPair<FString, TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>>& Entry : ReceiverInstances)
	{
		if (Entry.Value.IsValid() && Entry.Value->IsReceiving())
		{
			ActiveNames.Add(Entry.Key);
		}
	}

	return ActiveNames;
}

FString FGPUTextureShareReceiver::GetLastError() const
{
	FScopeLock Lock(&LastErrorMutex);
	return LastError;
}

void FGPUTextureShareReceiver::Shutdown()
{
	StopReceiver();
}

void FGPUTextureShareReceiver::SetLastError(const FString& InError, bool bLogAsWarning)
{
	if (InError.IsEmpty())
	{
		return;
	}

	bool bChanged = false;
	{
		FScopeLock Lock(&LastErrorMutex);
		if (LastError != InError)
		{
			LastError = InError;
			bChanged = true;
		}
	}

	if (bChanged && bLogAsWarning)
	{
		UE_LOG(LogGPUTextureShare, Warning, TEXT("%s"), *InError);
	}
}

void FGPUTextureShareReceiver::ClearLastError()
{
	FScopeLock Lock(&LastErrorMutex);
	LastError.Reset();
}

void FGPUTextureShareReceiver::PruneStoppedReceivers_NoLock()
{
	for (auto It = ReceiverInstances.CreateIterator(); It; ++It)
	{
		if (!It.Value().IsValid() || !It.Value()->IsReceiving())
		{
			It.RemoveCurrent();
		}
	}
}

FString FGPUTextureShareReceiver::NormalizeSharedName(const FString& SharedName) const
{
	return SharedName.TrimStartAndEnd();
}

