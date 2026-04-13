#include "GPUTextureShareSharedMemory.h"

#include "GPUTextureShare.h"

#include "Misc/ScopeLock.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#endif

FGPUTextureShareSharedMemoryWriter::FGPUTextureShareSharedMemoryWriter()
{
}

FGPUTextureShareSharedMemoryWriter::~FGPUTextureShareSharedMemoryWriter()
{
	Close();
}

bool FGPUTextureShareSharedMemoryWriter::Open(const FString& InMappingName, FString* OutError)
{
	const FString TrimmedName = InMappingName.TrimStartAndEnd();
	if (TrimmedName.IsEmpty())
	{
		if (OutError)
		{
			*OutError = TEXT("Open shared memory failed: mapping name is empty.");
		}
		return false;
	}

#if !PLATFORM_WINDOWS
	if (OutError)
	{
		*OutError = TEXT("Open shared memory failed: only Windows is supported.");
	}
	return false;
#else
	Close();

	HANDLE NewHandle = CreateFileMappingW(
		INVALID_HANDLE_VALUE,
		nullptr,
		PAGE_READWRITE,
		0,
		static_cast<DWORD>(sizeof(GPUTextureShareProtocol::FFrameHeaderV1)),
		*TrimmedName);

	if (NewHandle == nullptr)
	{
		const DWORD WinErr = GetLastError();
		if (OutError)
		{
			*OutError = FString::Printf(TEXT("CreateFileMappingW('%s') failed. WinErr=%u"), *TrimmedName, WinErr);
		}
		return false;
	}

	void* NewView = MapViewOfFile(NewHandle, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(GPUTextureShareProtocol::FFrameHeaderV1));
	if (NewView == nullptr)
	{
		const DWORD WinErr = GetLastError();
		CloseHandle(NewHandle);
		if (OutError)
		{
			*OutError = FString::Printf(TEXT("MapViewOfFile('%s') failed. WinErr=%u"), *TrimmedName, WinErr);
		}
		return false;
	}

	GPUTextureShareProtocol::FFrameHeaderV1 InitialHeader = {};
	FMemory::Memcpy(NewView, &InitialHeader, sizeof(InitialHeader));

	{
		FScopeLock Lock(&Mutex);
		MappingName = TrimmedName;
		MappingHandle = NewHandle;
		MappingView = NewView;
	}

	UE_LOG(LogGPUTextureShare, Log, TEXT("Shared memory opened. Mapping='%s'"), *TrimmedName);
	return true;
#endif
}

void FGPUTextureShareSharedMemoryWriter::Close()
{
#if PLATFORM_WINDOWS
	HANDLE HandleToClose = nullptr;
	void* ViewToClose = nullptr;
	FString ClosedName;
	{
		FScopeLock Lock(&Mutex);
		HandleToClose = static_cast<HANDLE>(MappingHandle);
		ViewToClose = MappingView;
		ClosedName = MappingName;
		MappingHandle = nullptr;
		MappingView = nullptr;
		MappingName.Reset();
	}

	if (ViewToClose)
	{
		UnmapViewOfFile(ViewToClose);
	}

	if (HandleToClose)
	{
		CloseHandle(HandleToClose);
	}

	if (!ClosedName.IsEmpty())
	{
		UE_LOG(LogGPUTextureShare, Log, TEXT("Shared memory closed. Mapping='%s'"), *ClosedName);
	}
#else
	FScopeLock Lock(&Mutex);
	MappingName.Reset();
	MappingHandle = nullptr;
	MappingView = nullptr;
#endif
}

bool FGPUTextureShareSharedMemoryWriter::IsOpen() const
{
	FScopeLock Lock(&Mutex);
	return MappingHandle != nullptr && MappingView != nullptr;
}

bool FGPUTextureShareSharedMemoryWriter::Publish(const GPUTextureShareProtocol::FFrameHeaderV1& Header, FString* OutError)
{
	void* View = nullptr;
	{
		FScopeLock Lock(&Mutex);
		View = MappingView;
	}

	if (View == nullptr)
	{
		if (OutError)
		{
			*OutError = TEXT("Publish failed: shared memory is not open.");
		}
		return false;
	}

	FMemory::Memcpy(View, &Header, sizeof(Header));
	return true;
}

FString FGPUTextureShareSharedMemoryWriter::GetMappingName() const
{
	FScopeLock Lock(&Mutex);
	return MappingName;
}
