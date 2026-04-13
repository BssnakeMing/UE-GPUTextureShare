#pragma once

#include "CoreMinimal.h"

class UTextureRenderTarget2D;
class FGPUTextureShareSenderInstance;

class GPUTEXTURESHARE_API FGPUTextureShareSender
{
public:
	FGPUTextureShareSender();
	~FGPUTextureShareSender();

	bool StartSender(const FString& SharedName, UTextureRenderTarget2D* InSourceRenderTarget);
	bool StopSenderByName(const FString& SharedName);
	void StopSender();
	bool IsSendingByName(const FString& SharedName) const;
	bool IsSending() const;
	FString GetLastErrorByName(const FString& SharedName) const;
	TArray<FString> GetActiveSenderNames() const;
	FString GetLastError() const;
	void Shutdown();

private:
	void SetLastError(const FString& InError, bool bLogAsWarning = true);
	void ClearLastError();
	void PruneStoppedSenders_NoLock();
	FString NormalizeSharedName(const FString& SharedName) const;

	mutable FCriticalSection LastErrorMutex;
	mutable FCriticalSection ManagerMutex;

	FString LastError;
	TMap<FString, TSharedPtr<FGPUTextureShareSenderInstance, ESPMode::ThreadSafe>> SenderInstances;
};
