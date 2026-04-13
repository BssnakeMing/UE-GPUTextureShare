// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UTextureRenderTarget2D;
class FGPUTextureShareReceiverInstance;

class GPUTEXTURESHARE_API FGPUTextureShareReceiver
{
public:
	FGPUTextureShareReceiver();
	~FGPUTextureShareReceiver();

	bool StartReceiver(const FString& SharedName, UTextureRenderTarget2D* InTargetRenderTarget);
	bool StopReceiverByName(const FString& SharedName);
	void StopReceiver();
	bool IsReceivingByName(const FString& SharedName) const;
	bool IsReceiving() const;
	FString GetLastErrorByName(const FString& SharedName) const;
	TArray<FString> GetActiveReceiverNames() const;
	FString GetLastError() const;
	void Shutdown();

private:
	void SetLastError(const FString& InError, bool bLogAsWarning = true);
	void ClearLastError();
	void PruneStoppedReceivers_NoLock();
	FString NormalizeSharedName(const FString& SharedName) const;

	mutable FCriticalSection LastErrorMutex;
	mutable FCriticalSection ManagerMutex;

	FString LastError;
	TMap<FString, TSharedPtr<FGPUTextureShareReceiverInstance, ESPMode::ThreadSafe>> ReceiverInstances;
};
