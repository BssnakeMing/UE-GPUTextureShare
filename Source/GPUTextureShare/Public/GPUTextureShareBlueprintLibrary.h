// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GPUTextureShareBlueprintLibrary.generated.h"

class UTextureRenderTarget2D;

UCLASS()
class GPUTEXTURESHARE_API UGPUTextureShareBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GPUTextureShare|Sender")
	static bool StartSender(const FString& SharedName, UTextureRenderTarget2D* SourceRenderTarget);

	UFUNCTION(BlueprintCallable, Category = "GPUTextureShare|Sender")
	static void StopSender();

	UFUNCTION(BlueprintCallable, Category = "GPUTextureShare|Sender")
	static bool StopSenderByName(const FString& SharedName);

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Sender")
	static bool IsSending();

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Sender")
	static bool IsSendingByName(const FString& SharedName);

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Sender")
	static FString GetSenderLastError();

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Sender")
	static FString GetSenderLastErrorByName(const FString& SharedName);

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Sender")
	static TArray<FString> GetActiveSenderNames();

	UFUNCTION(BlueprintCallable, Category = "GPUTextureShare|Receiver")
	static bool StartReceiver(const FString& SharedName, UTextureRenderTarget2D* TargetRenderTarget);

	UFUNCTION(BlueprintCallable, Category = "GPUTextureShare|Receiver")
	static void StopReceiver();

	UFUNCTION(BlueprintCallable, Category = "GPUTextureShare|Receiver")
	static bool StopReceiverByName(const FString& SharedName);

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Receiver")
	static bool IsReceiving();

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Receiver")
	static bool IsReceivingByName(const FString& SharedName);

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Receiver")
	static FString GetLastError();

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Receiver")
	static FString GetLastErrorByName(const FString& SharedName);

	UFUNCTION(BlueprintPure, Category = "GPUTextureShare|Receiver")
	static TArray<FString> GetActiveReceiverNames();
};
