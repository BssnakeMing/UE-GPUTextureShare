// Copyright Epic Games, Inc. All Rights Reserved.

#include "GPUTextureShareBlueprintLibrary.h"

#include "GPUTextureShare.h"
#include "GPUTextureShareReceiver.h"
#include "GPUTextureShareSender.h"

namespace
{
	FGPUTextureShareReceiver* GetReceiver()
	{
		if (FGPUTextureShareModule::IsAvailable())
		{
			return &FGPUTextureShareModule::Get().GetReceiver();
		}

		if (FGPUTextureShareModule* Module = FModuleManager::LoadModulePtr<FGPUTextureShareModule>(TEXT("GPUTextureShare")))
		{
			return &Module->GetReceiver();
		}

		return nullptr;
	}

	FGPUTextureShareSender* GetSender()
	{
		if (FGPUTextureShareModule::IsAvailable())
		{
			return &FGPUTextureShareModule::Get().GetSender();
		}

		if (FGPUTextureShareModule* Module = FModuleManager::LoadModulePtr<FGPUTextureShareModule>(TEXT("GPUTextureShare")))
		{
			return &Module->GetSender();
		}

		return nullptr;
	}

	
}

bool UGPUTextureShareBlueprintLibrary::StartSender(const FString& SharedName, UTextureRenderTarget2D* SourceRenderTarget)
{
	// todo 先查找是否已有发送SharedName，如果有则结束掉相关句柄
	if (FGPUTextureShareSender* Sender = GetSender())
	{
		return Sender->StartSender(SharedName, SourceRenderTarget);
	}
	UE_LOG(LogGPUTextureShare, Warning, TEXT("GPUTextureShare module is not available."));
	return false;
}

void UGPUTextureShareBlueprintLibrary::StopSender()
{
	if (FGPUTextureShareSender* Sender = GetSender())
	{
		Sender->StopSender();
	}
	// todo 再程序结束或结束游戏时自动停止
}

bool UGPUTextureShareBlueprintLibrary::StopSenderByName(const FString& SharedName)
{
	if (FGPUTextureShareSender* Sender = GetSender())
	{
		return Sender->StopSenderByName(SharedName);
	}
	return false;
}

bool UGPUTextureShareBlueprintLibrary::IsSending()
{
	if (FGPUTextureShareSender* Sender = GetSender())
	{
		return Sender->IsSending();
	}
	return false;
}

bool UGPUTextureShareBlueprintLibrary::IsSendingByName(const FString& SharedName)
{
	if (FGPUTextureShareSender* Sender = GetSender())
	{
		return Sender->IsSendingByName(SharedName);
	}
	return false;
}

FString UGPUTextureShareBlueprintLibrary::GetSenderLastError()
{
	if (FGPUTextureShareSender* Sender = GetSender())
	{
		return Sender->GetLastError();
	}
	return TEXT("GPUTextureShare module is not available.");
}

FString UGPUTextureShareBlueprintLibrary::GetSenderLastErrorByName(const FString& SharedName)
{
	if (FGPUTextureShareSender* Sender = GetSender())
	{
		return Sender->GetLastErrorByName(SharedName);
	}
	return TEXT("GPUTextureShare module is not available.");
}

TArray<FString> UGPUTextureShareBlueprintLibrary::GetActiveSenderNames()
{
	if (FGPUTextureShareSender* Sender = GetSender())
	{
		return Sender->GetActiveSenderNames();
	}
	return TArray<FString>();
}

bool UGPUTextureShareBlueprintLibrary::StartReceiver(const FString& SharedName, UTextureRenderTarget2D* TargetRenderTarget)
{
	if (FGPUTextureShareReceiver* Receiver = GetReceiver())
	{
		return Receiver->StartReceiver(SharedName, TargetRenderTarget);
	}

	UE_LOG(LogGPUTextureShare, Warning, TEXT("GPUTextureShare module is not available."));
	return false;
}

void UGPUTextureShareBlueprintLibrary::StopReceiver()
{
	if (FGPUTextureShareReceiver* Receiver = GetReceiver())
	{
		Receiver->StopReceiver();
	}
}

bool UGPUTextureShareBlueprintLibrary::StopReceiverByName(const FString& SharedName)
{
	if (FGPUTextureShareReceiver* Receiver = GetReceiver())
	{
		return Receiver->StopReceiverByName(SharedName);
	}

	return false;
}

bool UGPUTextureShareBlueprintLibrary::IsReceiving()
{
	if (FGPUTextureShareReceiver* Receiver = GetReceiver())
	{
		return Receiver->IsReceiving();
	}

	return false;
}

bool UGPUTextureShareBlueprintLibrary::IsReceivingByName(const FString& SharedName)
{
	if (FGPUTextureShareReceiver* Receiver = GetReceiver())
	{
		return Receiver->IsReceivingByName(SharedName);
	}

	return false;
}

FString UGPUTextureShareBlueprintLibrary::GetLastError()
{
	if (FGPUTextureShareReceiver* Receiver = GetReceiver())
	{
		return Receiver->GetLastError();
	}

	return TEXT("GPUTextureShare module is not available.");
}

FString UGPUTextureShareBlueprintLibrary::GetLastErrorByName(const FString& SharedName)
{
	if (FGPUTextureShareReceiver* Receiver = GetReceiver())
	{
		return Receiver->GetLastErrorByName(SharedName);
	}

	return TEXT("GPUTextureShare module is not available.");
}

TArray<FString> UGPUTextureShareBlueprintLibrary::GetActiveReceiverNames()
{
	if (FGPUTextureShareReceiver* Receiver = GetReceiver())
	{
		return Receiver->GetActiveReceiverNames();
	}

	return TArray<FString>();
}
