// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGPUTextureShare, Log, All);

class FGPUTextureShareReceiver;
class FGPUTextureShareSender;

class FGPUTextureShareModule : public IModuleInterface
{
public:
	static FGPUTextureShareModule& Get();
	static bool IsAvailable();

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	FGPUTextureShareReceiver& GetReceiver();
	FGPUTextureShareSender& GetSender();

private:
	TUniquePtr<FGPUTextureShareReceiver> Receiver;
	TUniquePtr<FGPUTextureShareSender> Sender;
};
