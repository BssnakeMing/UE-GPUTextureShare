// Copyright Epic Games, Inc. All Rights Reserved.

#include "GPUTextureShare.h"

#include "GPUTextureShareReceiver.h"
#include "GPUTextureShareSender.h"


DEFINE_LOG_CATEGORY(LogGPUTextureShare);

FGPUTextureShareModule& FGPUTextureShareModule::Get()
{
	return FModuleManager::LoadModuleChecked<FGPUTextureShareModule>(TEXT("GPUTextureShare"));
}

bool FGPUTextureShareModule::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded(TEXT("GPUTextureShare"));
}

void FGPUTextureShareModule::StartupModule()
{
	Receiver = MakeUnique<FGPUTextureShareReceiver>();
	Sender = MakeUnique<FGPUTextureShareSender>();
}

void FGPUTextureShareModule::ShutdownModule()
{
	if (Sender)
	{
		Sender->Shutdown();
		Sender.Reset();
	}

	if (Receiver)
	{
		Receiver->Shutdown();
		Receiver.Reset();
	}
}

FGPUTextureShareReceiver& FGPUTextureShareModule::GetReceiver()
{
	if (!Receiver)
	{
		Receiver = MakeUnique<FGPUTextureShareReceiver>();
	}

	return *Receiver;
}

FGPUTextureShareSender& FGPUTextureShareModule::GetSender()
{
	if (!Sender)
	{
		Sender = MakeUnique<FGPUTextureShareSender>();
	}

	return *Sender;
}



IMPLEMENT_MODULE(FGPUTextureShareModule, GPUTextureShare)
