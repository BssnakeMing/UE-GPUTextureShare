#pragma once

#include "CoreMinimal.h"
#include "GPUTextureShareProtocol.h"

class FGPUTextureShareSharedMemoryWriter : public TSharedFromThis<FGPUTextureShareSharedMemoryWriter, ESPMode::ThreadSafe>
{
public:
	FGPUTextureShareSharedMemoryWriter();
	~FGPUTextureShareSharedMemoryWriter();

	bool Open(const FString& InMappingName, FString* OutError = nullptr);
	void Close();
	bool IsOpen() const;
	bool Publish(const GPUTextureShareProtocol::FFrameHeaderV1& Header, FString* OutError = nullptr);
	FString GetMappingName() const;

private:
	mutable FCriticalSection Mutex;
	FString MappingName;
	void* MappingHandle = nullptr;
	void* MappingView = nullptr;
};
