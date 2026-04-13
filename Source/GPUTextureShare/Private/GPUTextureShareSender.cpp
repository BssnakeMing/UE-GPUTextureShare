#include "GPUTextureShareSender.h"

#include "GPUTextureShare.h"
#include "GPUTextureShareProtocol.h"
#include "GPUTextureShareSharedMemory.h"

#include "Containers/Ticker.h"
#include "DynamicRHI.h"
#include "Engine/TextureRenderTarget2D.h"
#include "HAL/PlatformTime.h"
#include "Misc/ScopeLock.h"
#include "RHICommandList.h"
#include "RenderingThread.h"
#include "TextureResource.h"

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

class FGPUTextureShareSenderDiagnostics : public TSharedFromThis<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>
{
public:
	void SetLastError(const FString& InError, bool bLogAsWarning = true)
	{
		if (InError.IsEmpty())
		{
			return;
		}

		bool bChanged = false;
		{
			FScopeLock Lock(&Mutex);
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

	void ClearLastError()
	{
		FScopeLock Lock(&Mutex);
		LastError.Reset();
	}

	FString GetLastError() const
	{
		FScopeLock Lock(&Mutex);
		return LastError;
	}

private:
	mutable FCriticalSection Mutex;
	FString LastError;
};

class FGPUTextureShareSenderInstance : public TSharedFromThis<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>
{
public:
	class FRenderBridgeState;

	FGPUTextureShareSenderInstance();
	~FGPUTextureShareSenderInstance();

	bool StartSender(const FString& SharedName, UTextureRenderTarget2D* InSourceRenderTarget);
	void StopSender();
	bool IsSending() const;
	FString GetLastError() const;
	void Shutdown();

private:
	bool Tick(float DeltaTime);

	mutable FCriticalSection StateMutex;
	TWeakObjectPtr<UTextureRenderTarget2D> SourceRenderTarget;
	FString SharedMemoryName;
	FTSTicker::FDelegateHandle TickHandle;
	bool bIsSending = false;
	bool bLoggedCompatibilityMode = false;

	TSharedPtr<FGPUTextureShareSharedMemoryWriter, ESPMode::ThreadSafe> SharedMemory;
	TSharedPtr<FRenderBridgeState, ESPMode::ThreadSafe> RenderBridgeState;
	TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe> Diagnostics;
};

class FGPUTextureShareSenderInstance::FRenderBridgeState : public TSharedFromThis<FGPUTextureShareSenderInstance::FRenderBridgeState, ESPMode::ThreadSafe>
{
public:
	void Tick_RenderThread(
		FRHICommandListImmediate& RHICmdList,
		const FTextureRHIRef& SourceTexture,
		bool bSourceSRGB,
		const FString& SharedName,
		const TSharedPtr<FGPUTextureShareSharedMemoryWriter, ESPMode::ThreadSafe>& SharedMemoryWriter,
		const TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>& InDiagnostics);

	void Shutdown_RenderThread();

private:
#if PLATFORM_WINDOWS
	bool EnsureBridgeInitialized(const TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>& InDiagnostics);
	bool EnsureWrappedSource(FRHITexture* SourceTextureRHI, ID3D12Resource* NativeSourceResource, const TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>& InDiagnostics);
	bool EnsureSharedTexture(const D3D12_RESOURCE_DESC& SourceDesc, bool bSourceSRGB, const TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>& InDiagnostics);
	void InvalidateWrappedSource();
	void InvalidateSharedTexture();

	Microsoft::WRL::ComPtr<ID3D12Device> D3D12Device;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> GraphicsQueue;
	Microsoft::WRL::ComPtr<ID3D11Device> D3D11Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> D3D11DeviceContext;
	Microsoft::WRL::ComPtr<ID3D11On12Device> D3D11On12Device;

	Microsoft::WRL::ComPtr<ID3D11Resource> WrappedSourceResource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> WrappedSourceTexture;
	void* WrappedSourceNativeResource = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> SharedTexture;
	DXGI_FORMAT SharedFormat = DXGI_FORMAT_UNKNOWN;
	uint32 SharedWidth = 0;
	uint32 SharedHeight = 0;
	uint64 SharedHandleValue = 0;
	uint64 Generation = 0;
	uint64 FrameId = 0;

	bool bBridgeInitialized = false;
#endif
};

#if PLATFORM_WINDOWS
namespace
{
	FString HResultToString(HRESULT Hr)
	{
		return FString::Printf(TEXT("0x%08x"), static_cast<uint32>(Hr));
	}

	DXGI_FORMAT NormalizeSharedFormat(DXGI_FORMAT InFormat, bool bPreferSRGB)
	{
		(void)bPreferSRGB;

		switch (InFormat)
		{
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
			return DXGI_FORMAT_B8G8R8A8_UNORM;
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
			return DXGI_FORMAT_B8G8R8X8_UNORM;
		case DXGI_FORMAT_R10G10B10A2_TYPELESS:
			return DXGI_FORMAT_R10G10B10A2_UNORM;
		case DXGI_FORMAT_R16G16B16A16_TYPELESS:
			return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case DXGI_FORMAT_R16G16_TYPELESS:
			return DXGI_FORMAT_R16G16_UNORM;
		case DXGI_FORMAT_R16_TYPELESS:
			return DXGI_FORMAT_R16_UNORM;
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case DXGI_FORMAT_R32G32_TYPELESS:
			return DXGI_FORMAT_R32G32_FLOAT;
		case DXGI_FORMAT_R32_TYPELESS:
			return DXGI_FORMAT_R32_FLOAT;
		default:
			return InFormat;
		}
	}

	bool IsSRGBFormat(DXGI_FORMAT InFormat)
	{
		switch (InFormat)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
			return true;
		default:
			return false;
		}
	}

	bool HasAlphaChannel(DXGI_FORMAT InFormat)
	{
		switch (InFormat)
		{
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		case DXGI_FORMAT_B8G8R8A8_UNORM:
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		case DXGI_FORMAT_R10G10B10A2_UNORM:
		case DXGI_FORMAT_R10G10B10A2_UINT:
		case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		case DXGI_FORMAT_R16G16B16A16_FLOAT:
		case DXGI_FORMAT_R16G16B16A16_UNORM:
		case DXGI_FORMAT_R16G16B16A16_UINT:
		case DXGI_FORMAT_R16G16B16A16_SNORM:
		case DXGI_FORMAT_R16G16B16A16_SINT:
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
		case DXGI_FORMAT_A8_UNORM:
		case DXGI_FORMAT_BC1_TYPELESS:
		case DXGI_FORMAT_BC1_UNORM:
		case DXGI_FORMAT_BC1_UNORM_SRGB:
		case DXGI_FORMAT_BC2_TYPELESS:
		case DXGI_FORMAT_BC2_UNORM:
		case DXGI_FORMAT_BC2_UNORM_SRGB:
		case DXGI_FORMAT_BC3_TYPELESS:
		case DXGI_FORMAT_BC3_UNORM:
		case DXGI_FORMAT_BC3_UNORM_SRGB:
		case DXGI_FORMAT_BC7_TYPELESS:
		case DXGI_FORMAT_BC7_UNORM:
		case DXGI_FORMAT_BC7_UNORM_SRGB:
		case DXGI_FORMAT_B4G4R4A4_UNORM:
			return true;
		default:
			return false;
		}
	}
}
#endif

FGPUTextureShareSenderInstance::FGPUTextureShareSenderInstance()
{
	Diagnostics = MakeShared<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>();
}

FGPUTextureShareSenderInstance::~FGPUTextureShareSenderInstance()
{
	Shutdown();
}

bool FGPUTextureShareSenderInstance::StartSender(const FString& SharedName, UTextureRenderTarget2D* InSourceRenderTarget)
{
	const FString TrimmedSharedName = SharedName.TrimStartAndEnd();
	if (TrimmedSharedName.IsEmpty())
	{
		Diagnostics->SetLastError(TEXT("StartSender failed: shared mapping name is empty."));
		return false;
	}

	if (InSourceRenderTarget == nullptr)
	{
		Diagnostics->SetLastError(TEXT("StartSender failed: source UTextureRenderTarget2D is null."));
		return false;
	}

#if !PLATFORM_WINDOWS
	Diagnostics->SetLastError(TEXT("StartSender is only supported on Windows."));
	return false;
#else
	if (GDynamicRHI == nullptr)
	{
		Diagnostics->SetLastError(TEXT("StartSender failed: RHI is not initialized."));
		return false;
	}

	const FString RHIName = GDynamicRHI->GetName();
	if (!RHIName.Contains(TEXT("D3D12"), ESearchCase::IgnoreCase))
	{
		Diagnostics->SetLastError(FString::Printf(TEXT("StartSender failed: current RHI is '%s', only D3D12 is supported."), *RHIName));
		return false;
	}

	StopSender();

	TSharedPtr<FGPUTextureShareSharedMemoryWriter, ESPMode::ThreadSafe> NewSharedMemory = MakeShared<FGPUTextureShareSharedMemoryWriter, ESPMode::ThreadSafe>();
	FString SharedMemoryError;
	if (!NewSharedMemory->Open(TrimmedSharedName, &SharedMemoryError))
	{
		Diagnostics->SetLastError(SharedMemoryError.IsEmpty() ? TEXT("StartSender failed: cannot open shared memory.") : SharedMemoryError);
		return false;
	}

	{
		FScopeLock StateLock(&StateMutex);
		SharedMemoryName = TrimmedSharedName;
		SourceRenderTarget = InSourceRenderTarget;
		SharedMemory = NewSharedMemory;
		RenderBridgeState = MakeShared<FRenderBridgeState, ESPMode::ThreadSafe>();
		bIsSending = true;
		bLoggedCompatibilityMode = false;
	}

	Diagnostics->ClearLastError();

	if (TickHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
		TickHandle.Reset();
	}
	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FGPUTextureShareSenderInstance::Tick));

	UE_LOG(LogGPUTextureShare, Log, TEXT("Sender started. Mapping='%s', Source='%s'"), *TrimmedSharedName, *GetNameSafe(InSourceRenderTarget));
	UE_LOG(LogGPUTextureShare, Log, TEXT("Sender '%s' sync mode is None (KeyedMutex disabled)."), *TrimmedSharedName);
	if (!bLoggedCompatibilityMode)
	{
		UE_LOG(LogGPUTextureShare, Log, TEXT("Sender '%s' running in metadata compatibility mode (兼容模式): legacy handle fields are published."), *TrimmedSharedName);
		bLoggedCompatibilityMode = true;
	}
	return true;
#endif
}

void FGPUTextureShareSenderInstance::StopSender()
{
	FTSTicker::FDelegateHandle LocalTickHandle;
	TSharedPtr<FRenderBridgeState, ESPMode::ThreadSafe> RenderStateToShutdown;
	TSharedPtr<FGPUTextureShareSharedMemoryWriter, ESPMode::ThreadSafe> SharedMemoryToClose;
	bool bWasActive = false;

	{
		FScopeLock StateLock(&StateMutex);
		bWasActive = bIsSending || TickHandle.IsValid() || RenderBridgeState.IsValid() || SharedMemory.IsValid();
		bIsSending = false;
		SourceRenderTarget.Reset();
		SharedMemoryName.Reset();
		bLoggedCompatibilityMode = false;
		LocalTickHandle = TickHandle;
		TickHandle.Reset();
		RenderStateToShutdown = MoveTemp(RenderBridgeState);
		SharedMemoryToClose = MoveTemp(SharedMemory);
	}

	if (LocalTickHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(LocalTickHandle);
	}

	if (RenderStateToShutdown.IsValid())
	{
		if (IsInRenderingThread())
		{
			RenderStateToShutdown->Shutdown_RenderThread();
		}
		else
		{
			ENQUEUE_RENDER_COMMAND(GPUTextureShare_StopSenderRenderState)(
				[RenderStateToShutdown](FRHICommandListImmediate& RHICmdList)
				{
					(void)RHICmdList;
					RenderStateToShutdown->Shutdown_RenderThread();
				});
			FlushRenderingCommands();
		}
	}

	if (SharedMemoryToClose.IsValid())
	{
		SharedMemoryToClose->Close();
	}

	if (bWasActive)
	{
		UE_LOG(LogGPUTextureShare, Log, TEXT("Sender stopped."));
	}
}

bool FGPUTextureShareSenderInstance::IsSending() const
{
	FScopeLock StateLock(&StateMutex);
	return bIsSending;
}

FString FGPUTextureShareSenderInstance::GetLastError() const
{
	if (Diagnostics.IsValid())
	{
		return Diagnostics->GetLastError();
	}

	return TEXT("Sender diagnostics are unavailable.");
}

void FGPUTextureShareSenderInstance::Shutdown()
{
	StopSender();
}

bool FGPUTextureShareSenderInstance::Tick(float DeltaTime)
{
	(void)DeltaTime;

	TWeakObjectPtr<UTextureRenderTarget2D> SourceTarget;
	TSharedPtr<FRenderBridgeState, ESPMode::ThreadSafe> RenderState;
	TSharedPtr<FGPUTextureShareSharedMemoryWriter, ESPMode::ThreadSafe> SharedMemoryWriter;
	FString SharedName;
	bool bActive = false;

	{
		FScopeLock StateLock(&StateMutex);
		bActive = bIsSending;
		SourceTarget = SourceRenderTarget;
		RenderState = RenderBridgeState;
		SharedMemoryWriter = SharedMemory;
		SharedName = SharedMemoryName;
	}

	if (!bActive)
	{
		return false;
	}

	UTextureRenderTarget2D* SourceTargetObject = SourceTarget.Get();
	if (SourceTargetObject == nullptr)
	{
		if (Diagnostics.IsValid())
		{
			Diagnostics->SetLastError(TEXT("Source render target is no longer valid. Sender stopped."));
		}
		StopSender();
		return false;
	}

	if (!RenderState.IsValid() || !SharedMemoryWriter.IsValid() || !SharedMemoryWriter->IsOpen())
	{
		if (Diagnostics.IsValid())
		{
			Diagnostics->SetLastError(TEXT("Sender tick failed: render bridge or shared memory is unavailable."));
		}
		return true;
	}

	FTextureRenderTargetResource* RenderTargetResource = SourceTargetObject->GameThread_GetRenderTargetResource();
	if (RenderTargetResource == nullptr)
	{
		return true;
	}

	const FTextureRHIRef SourceTexture = RenderTargetResource->GetRenderTargetTexture();
	if (!SourceTexture.IsValid())
	{
		return true;
	}

	const bool bSourceSRGB = (SourceTargetObject->RenderTargetFormat == RTF_RGBA8_SRGB);

	ENQUEUE_RENDER_COMMAND(GPUTextureShare_SenderCopy)(
		[RenderState, SourceTexture, bSourceSRGB, SharedName, SharedMemoryWriter, LocalDiagnostics = Diagnostics](FRHICommandListImmediate& RHICmdList)
		{
			RenderState->Tick_RenderThread(RHICmdList, SourceTexture, bSourceSRGB, SharedName, SharedMemoryWriter, LocalDiagnostics);
		});

	return true;
}

void FGPUTextureShareSenderInstance::FRenderBridgeState::Tick_RenderThread(
	FRHICommandListImmediate& RHICmdList,
	const FTextureRHIRef& SourceTexture,
	bool bSourceSRGB,
	const FString& SharedName,
	const TSharedPtr<FGPUTextureShareSharedMemoryWriter, ESPMode::ThreadSafe>& SharedMemoryWriter,
	const TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>& InDiagnostics)
{
#if !PLATFORM_WINDOWS
	(void)RHICmdList;
	(void)SourceTexture;
	(void)SharedName;
	(void)SharedMemoryWriter;
	(void)InDiagnostics;
#else
	if (!SourceTexture.IsValid() || !SharedMemoryWriter.IsValid())
	{
		return;
	}

	if (!EnsureBridgeInitialized(InDiagnostics))
	{
		return;
	}

	FRHITexture* SourceTextureRHI = SourceTexture.GetReference();
	if (SourceTextureRHI == nullptr)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(TEXT("Sender render tick failed: source RHI texture is null."), false);
		}
		return;
	}

	void* NativeResource = SourceTextureRHI->GetNativeResource();
	if (NativeResource == nullptr)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(TEXT("Sender render tick failed: source native D3D12 resource is null."), false);
		}
		return;
	}

	ID3D12Resource* NativeSourceResource = reinterpret_cast<ID3D12Resource*>(NativeResource);
	const D3D12_RESOURCE_DESC SourceDesc = NativeSourceResource->GetDesc();

	if (SourceDesc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D || SourceDesc.SampleDesc.Count != 1 || SourceDesc.DepthOrArraySize != 1)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(
				FString::Printf(
					TEXT("Source texture is unsupported for sharing. Dimension=%u SampleCount=%u ArraySize=%u"),
					static_cast<uint32>(SourceDesc.Dimension),
					static_cast<uint32>(SourceDesc.SampleDesc.Count),
					static_cast<uint32>(SourceDesc.DepthOrArraySize)),
				false);
		}
		return;
	}

	if (!EnsureWrappedSource(SourceTextureRHI, NativeSourceResource, InDiagnostics))
	{
		return;
	}

	if (!EnsureSharedTexture(SourceDesc, bSourceSRGB, InDiagnostics))
	{
		return;
	}

	RHICmdList.Transition(FRHITransitionInfo(SourceTextureRHI, ERHIAccess::Unknown, ERHIAccess::CopySrc));

	ID3D11Resource* WrappedResources[] = { WrappedSourceResource.Get() };
	D3D11On12Device->AcquireWrappedResources(WrappedResources, UE_ARRAY_COUNT(WrappedResources));

	D3D11_TEXTURE2D_DESC Source11Desc = {};
	D3D11_TEXTURE2D_DESC Shared11Desc = {};
	WrappedSourceTexture->GetDesc(&Source11Desc);
	SharedTexture->GetDesc(&Shared11Desc);

	const UINT CopyWidth = FMath::Min(Source11Desc.Width, Shared11Desc.Width);
	const UINT CopyHeight = FMath::Min(Source11Desc.Height, Shared11Desc.Height);
	if (CopyWidth > 0 && CopyHeight > 0)
	{
		if (CopyWidth == Source11Desc.Width
			&& CopyHeight == Source11Desc.Height
			&& Source11Desc.Width == Shared11Desc.Width
			&& Source11Desc.Height == Shared11Desc.Height)
		{
			D3D11DeviceContext->CopyResource(SharedTexture.Get(), WrappedSourceTexture.Get());
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
			D3D11DeviceContext->CopySubresourceRegion(SharedTexture.Get(), 0, 0, 0, 0, WrappedSourceTexture.Get(), 0, &CopyBox);
		}
	}

	D3D11On12Device->ReleaseWrappedResources(WrappedResources, UE_ARRAY_COUNT(WrappedResources));
	D3D11DeviceContext->Flush();

	RHICmdList.Transition(FRHITransitionInfo(SourceTextureRHI, ERHIAccess::CopySrc, ERHIAccess::SRVMask));

	const uint64 CurrentFrameId = ++FrameId;

	GPUTextureShareProtocol::FFrameHeaderV1 Header = {};
	Header.Magic = GPUTextureShareProtocol::Magic;
	Header.Version = GPUTextureShareProtocol::Version;
	Header.HeaderTag = GPUTextureShareProtocol::LegacyHeaderTagBase | (CurrentFrameId & 0xFFFFFFFFull);
	Header.TickMs = GetTickCount64();
	Header.ProducerPid64 = static_cast<uint64>(GetCurrentProcessId());
	Header.Handle = SharedHandleValue;
	Header.Width = SharedWidth;
	Header.Height = SharedHeight;
	Header.Format = static_cast<uint32>(SharedFormat);
	Header.SyncMode = static_cast<uint32>(GPUTextureShareProtocol::ESyncMode::None);
	Header.FrameId = CurrentFrameId;
	Header.Generation = Generation;
	Header.TimestampCycles64 = FPlatformTime::Cycles64();
	Header.ProducerPid = static_cast<uint32>(GetCurrentProcessId());
	Header.LegacySharedHandle = SharedHandleValue;
	FCString::Strncpy(Header.LegacyShortName, TEXT("UE"), UE_ARRAY_COUNT(Header.LegacyShortName));
	FCString::Snprintf(
		Header.LegacyDisplayName,
		UE_ARRAY_COUNT(Header.LegacyDisplayName),
		TEXT("%s 0x%llx"),
		*SharedName,
		static_cast<unsigned long long>(SharedHandleValue));
	FCStringAnsi::Snprintf(
		Header.LegacyHandleString,
		static_cast<int32>(UE_ARRAY_COUNT(Header.LegacyHandleString)),
		"0x%llx",
		static_cast<unsigned long long>(SharedHandleValue));

	FString PublishError;
	if (!SharedMemoryWriter->Publish(Header, &PublishError))
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(PublishError.IsEmpty() ? TEXT("Failed to publish sender metadata.") : PublishError, false);
		}
		return;
	}

	if (InDiagnostics.IsValid())
	{
		InDiagnostics->ClearLastError();
	}

	UE_LOG(LogGPUTextureShare, VeryVerbose, TEXT("Sender '%s' published frame=%llu generation=%llu handle=0x%llx"),
		*SharedName,
		Header.FrameId,
		Header.Generation,
		Header.Handle);
#endif
}

void FGPUTextureShareSenderInstance::FRenderBridgeState::Shutdown_RenderThread()
{
#if PLATFORM_WINDOWS
	InvalidateWrappedSource();
	InvalidateSharedTexture();
	D3D11On12Device.Reset();
	D3D11DeviceContext.Reset();
	D3D11Device.Reset();
	GraphicsQueue.Reset();
	D3D12Device.Reset();
	bBridgeInitialized = false;
#endif
}

#if PLATFORM_WINDOWS
bool FGPUTextureShareSenderInstance::FRenderBridgeState::EnsureBridgeInitialized(const TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>& InDiagnostics)
{
	if (bBridgeInitialized)
	{
		return true;
	}

	ID3D12Device* NativeDevice = static_cast<ID3D12Device*>(RHIGetNativeDevice());
	ID3D12CommandQueue* NativeGraphicsQueue = static_cast<ID3D12CommandQueue*>(RHIGetNativeGraphicsQueue());
	if (NativeDevice == nullptr || NativeGraphicsQueue == nullptr)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(TEXT("D3D11On12 init failed: native D3D12 device or queue is null."));
		}
		return false;
	}

	D3D12Device = NativeDevice;
	GraphicsQueue = NativeGraphicsQueue;

	IUnknown* Queues[] = { GraphicsQueue.Get() };
	const UINT DeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
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
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(FString::Printf(TEXT("D3D11On12CreateDevice failed: %s"), *HResultToString(Hr)));
		}
		return false;
	}

	Hr = D3D11Device.As(&D3D11On12Device);
	if (FAILED(Hr) || !D3D11On12Device)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(FString::Printf(TEXT("ID3D11On12Device query failed: %s"), *HResultToString(Hr)));
		}
		return false;
	}

	bBridgeInitialized = true;
	UE_LOG(LogGPUTextureShare, Log, TEXT("Sender D3D11On12 bridge initialized."));
	return true;
}

bool FGPUTextureShareSenderInstance::FRenderBridgeState::EnsureWrappedSource(
	FRHITexture* SourceTextureRHI,
	ID3D12Resource* NativeSourceResource,
	const TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>& InDiagnostics)
{
	if (SourceTextureRHI == nullptr || NativeSourceResource == nullptr)
	{
		return false;
	}

	void* NativePointer = reinterpret_cast<void*>(NativeSourceResource);
	if (WrappedSourceResource && WrappedSourceTexture && WrappedSourceNativeResource == NativePointer)
	{
		return true;
	}

	InvalidateWrappedSource();

	D3D11_RESOURCE_FLAGS ResourceFlags = {};
	HRESULT Hr = D3D11On12Device->CreateWrappedResource(
		reinterpret_cast<IUnknown*>(NativeSourceResource),
		&ResourceFlags,
		D3D12_RESOURCE_STATE_COPY_SOURCE,
		D3D12_RESOURCE_STATE_COPY_SOURCE,
		__uuidof(ID3D11Resource),
		reinterpret_cast<void**>(WrappedSourceResource.GetAddressOf()));

	if (FAILED(Hr) || !WrappedSourceResource)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(FString::Printf(TEXT("CreateWrappedResource(source) failed: %s"), *HResultToString(Hr)), false);
		}
		return false;
	}

	Hr = WrappedSourceResource.As(&WrappedSourceTexture);
	if (FAILED(Hr) || !WrappedSourceTexture)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(FString::Printf(TEXT("Wrapped source is not ID3D11Texture2D: %s"), *HResultToString(Hr)), false);
		}
		InvalidateWrappedSource();
		return false;
	}

	WrappedSourceNativeResource = NativePointer;
	return true;
}

bool FGPUTextureShareSenderInstance::FRenderBridgeState::EnsureSharedTexture(
	const D3D12_RESOURCE_DESC& SourceDesc,
	bool bSourceSRGB,
	const TSharedPtr<FGPUTextureShareSenderDiagnostics, ESPMode::ThreadSafe>& InDiagnostics)
{
	const DXGI_FORMAT SourceFormat = SourceDesc.Format;
	const DXGI_FORMAT ShareFormat = NormalizeSharedFormat(SourceFormat, bSourceSRGB);
	const uint32 SourceWidth = static_cast<uint32>(SourceDesc.Width);
	const uint32 SourceHeight = static_cast<uint32>(SourceDesc.Height);

	if (ShareFormat == DXGI_FORMAT_UNKNOWN || SourceWidth == 0 || SourceHeight == 0)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(TEXT("Invalid source texture format or size for shared texture."), false);
		}
		return false;
	}

	if (SharedTexture
		&& SharedFormat == ShareFormat
		&& SharedWidth == SourceWidth
		&& SharedHeight == SourceHeight
		&& SharedHandleValue != 0)
	{
		return true;
	}

	if (IsSRGBFormat(SourceFormat) && ShareFormat != SourceFormat)
	{
		UE_LOG(
			LogGPUTextureShare,
			Log,
			TEXT("Sender normalized source SRGB format %u to linear shared format %u to avoid cross-process gamma mismatch."),
			static_cast<uint32>(SourceFormat),
			static_cast<uint32>(ShareFormat));
	}

	InvalidateSharedTexture();

	D3D11_TEXTURE2D_DESC Desc = {};
	Desc.Width = SourceWidth;
	Desc.Height = SourceHeight;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = ShareFormat;
	Desc.SampleDesc.Count = 1;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;

	HRESULT Hr = D3D11Device->CreateTexture2D(&Desc, nullptr, SharedTexture.GetAddressOf());
	if (FAILED(Hr) || !SharedTexture)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(
				FString::Printf(
					TEXT("CreateTexture2D(shared) failed. Size=%ux%u Format=%u Hr=%s"),
					SourceWidth,
					SourceHeight,
					static_cast<uint32>(ShareFormat),
					*HResultToString(Hr)),
				false);
		}
		InvalidateSharedTexture();
		return false;
	}

	Microsoft::WRL::ComPtr<IDXGIResource> DXGIResource;
	Hr = SharedTexture.As(&DXGIResource);
	if (FAILED(Hr) || !DXGIResource)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(FString::Printf(TEXT("IDXGIResource query failed: %s"), *HResultToString(Hr)), false);
		}
		InvalidateSharedTexture();
		return false;
	}

	HANDLE SharedHandle = nullptr;
	Hr = DXGIResource->GetSharedHandle(&SharedHandle);
	if (FAILED(Hr) || SharedHandle == nullptr)
	{
		if (InDiagnostics.IsValid())
		{
			InDiagnostics->SetLastError(FString::Printf(TEXT("GetSharedHandle failed: %s"), *HResultToString(Hr)), false);
		}
		InvalidateSharedTexture();
		return false;
	}

	SharedFormat = ShareFormat;
	SharedWidth = SourceWidth;
	SharedHeight = SourceHeight;
	SharedHandleValue = static_cast<uint64>(reinterpret_cast<uintptr_t>(SharedHandle));
	++Generation;

	UE_LOG(LogGPUTextureShare, Log, TEXT("Sender shared texture rebuilt. Size=%ux%u SrcFormat=%u SharedFormat=%u SrcHasAlpha=%s SharedHasAlpha=%s Handle=0x%llx Generation=%llu"),
		SharedWidth,
		SharedHeight,
		static_cast<uint32>(SourceFormat),
		static_cast<uint32>(SharedFormat),
		HasAlphaChannel(SourceFormat) ? TEXT("Yes") : TEXT("No"),
		HasAlphaChannel(SharedFormat) ? TEXT("Yes") : TEXT("No"),
		SharedHandleValue,
		Generation);

	if (!HasAlphaChannel(SharedFormat))
	{
		UE_LOG(LogGPUTextureShare, Warning, TEXT("Sender shared format %u does not contain alpha channel. Alpha cannot be preserved."), static_cast<uint32>(SharedFormat));
	}

	return true;
}

void FGPUTextureShareSenderInstance::FRenderBridgeState::InvalidateWrappedSource()
{
	WrappedSourceTexture.Reset();
	WrappedSourceResource.Reset();
	WrappedSourceNativeResource = nullptr;
}

void FGPUTextureShareSenderInstance::FRenderBridgeState::InvalidateSharedTexture()
{
	SharedTexture.Reset();
	SharedFormat = DXGI_FORMAT_UNKNOWN;
	SharedWidth = 0;
	SharedHeight = 0;
	SharedHandleValue = 0;
}
#endif

FGPUTextureShareSender::FGPUTextureShareSender()
{
}

FGPUTextureShareSender::~FGPUTextureShareSender()
{
	Shutdown();
}

bool FGPUTextureShareSender::StartSender(const FString& SharedName, UTextureRenderTarget2D* InSourceRenderTarget)
{
	const FString NormalizedName = NormalizeSharedName(SharedName);
	if (NormalizedName.IsEmpty())
	{
		SetLastError(TEXT("StartSender failed: shared mapping name is empty."));
		return false;
	}
	
	if (IsSendingByName(NormalizedName))
	{
		StopSenderByName(NormalizedName);
	}

	TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe> SenderInstance;
	bool bCreated = false;
	{
		FScopeLock Lock(&ManagerMutex);
		PruneStoppedSenders_NoLock();

		if (TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>* Found = SenderInstances.Find(NormalizedName))
		{
			SenderInstance = *Found;
		}
		else
		{
			SenderInstance = MakeShared<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>();
			SenderInstances.Add(NormalizedName, SenderInstance);
			bCreated = true;
		}
	}

	if (!SenderInstance.IsValid() || !SenderInstance->StartSender(NormalizedName, InSourceRenderTarget))
	{
		const FString InstanceError = SenderInstance.IsValid() ? SenderInstance->GetLastError() : TEXT("Sender instance is invalid.");
		SetLastError(FString::Printf(TEXT("StartSender('%s') failed: %s"), *NormalizedName, *InstanceError));

		if (bCreated)
		{
			FScopeLock Lock(&ManagerMutex);
			if (TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>* Found = SenderInstances.Find(NormalizedName))
			{
				if (Found->Get() == SenderInstance.Get() && (!SenderInstance.IsValid() || !SenderInstance->IsSending()))
				{
					SenderInstances.Remove(NormalizedName);
				}
			}
		}

		return false;
	}

	ClearLastError();
	return true;
}

bool FGPUTextureShareSender::StopSenderByName(const FString& SharedName)
{
	const FString NormalizedName = NormalizeSharedName(SharedName);
	if (NormalizedName.IsEmpty())
	{
		return false;
	}

	TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe> SenderInstance;
	{
		FScopeLock Lock(&ManagerMutex);
		if (TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>* Found = SenderInstances.Find(NormalizedName))
		{
			SenderInstance = *Found;
			SenderInstances.Remove(NormalizedName);
		}
	}

	if (!SenderInstance.IsValid())
	{
		return false;
	}

	SenderInstance->StopSender();
	return true;
}

void FGPUTextureShareSender::StopSender()
{
	TMap<FString, TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>> InstancesToStop;
	{
		FScopeLock Lock(&ManagerMutex);
		InstancesToStop = MoveTemp(SenderInstances);
	}

	for (TPair<FString, TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>>& Entry : InstancesToStop)
	{
		if (Entry.Value.IsValid())
		{
			Entry.Value->StopSender();
		}
	}
}

bool FGPUTextureShareSender::IsSendingByName(const FString& SharedName) const
{
	const FString NormalizedName = NormalizeSharedName(SharedName);
	if (NormalizedName.IsEmpty())
	{
		return false;
	}

	TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe> SenderInstance;
	{
		FScopeLock Lock(&ManagerMutex);
		if (const TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>* Found = SenderInstances.Find(NormalizedName))
		{
			SenderInstance = *Found;
		}
	}

	return SenderInstance.IsValid() && SenderInstance->IsSending();
}

bool FGPUTextureShareSender::IsSending() const
{
	FScopeLock Lock(&ManagerMutex);
	for (const TPair<FString, TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>>& Entry : SenderInstances)
	{
		if (Entry.Value.IsValid() && Entry.Value->IsSending())
		{
			return true;
		}
	}

	return false;
}

FString FGPUTextureShareSender::GetLastErrorByName(const FString& SharedName) const
{
	const FString NormalizedName = NormalizeSharedName(SharedName);
	if (NormalizedName.IsEmpty())
	{
		return TEXT("Shared mapping name is empty.");
	}

	TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe> SenderInstance;
	{
		FScopeLock Lock(&ManagerMutex);
		if (const TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>* Found = SenderInstances.Find(NormalizedName))
		{
			SenderInstance = *Found;
		}
	}

	if (!SenderInstance.IsValid())
	{
		return FString::Printf(TEXT("Sender '%s' does not exist."), *NormalizedName);
	}

	return SenderInstance->GetLastError();
}

TArray<FString> FGPUTextureShareSender::GetActiveSenderNames() const
{
	TArray<FString> ActiveNames;
	FScopeLock Lock(&ManagerMutex);
	for (const TPair<FString, TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>>& Entry : SenderInstances)
	{
		if (Entry.Value.IsValid() && Entry.Value->IsSending())
		{
			ActiveNames.Add(Entry.Key);
		}
	}

	return ActiveNames;
}

FString FGPUTextureShareSender::GetLastError() const
{
	FScopeLock Lock(&LastErrorMutex);
	return LastError;
}

void FGPUTextureShareSender::Shutdown()
{
	StopSender();
}

void FGPUTextureShareSender::SetLastError(const FString& InError, bool bLogAsWarning)
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

void FGPUTextureShareSender::ClearLastError()
{
	FScopeLock Lock(&LastErrorMutex);
	LastError.Reset();
}

void FGPUTextureShareSender::PruneStoppedSenders_NoLock()
{
	for (auto It = SenderInstances.CreateIterator(); It; ++It)
	{
		if (!It.Value().IsValid() || !It.Value()->IsSending())
		{
			It.RemoveCurrent();
		}
	}
}

FString FGPUTextureShareSender::NormalizeSharedName(const FString& SharedName) const
{
	return SharedName.TrimStartAndEnd();
}
