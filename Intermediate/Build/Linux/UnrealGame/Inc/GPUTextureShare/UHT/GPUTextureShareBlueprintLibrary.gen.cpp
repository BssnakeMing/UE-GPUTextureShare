// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GPUTextureShare/Public/GPUTextureShareBlueprintLibrary.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGPUTextureShareBlueprintLibrary() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
GPUTEXTURESHARE_API UClass* Z_Construct_UClass_UGPUTextureShareBlueprintLibrary();
GPUTEXTURESHARE_API UClass* Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_NoRegister();
UPackage* Z_Construct_UPackage__Script_GPUTextureShare();
// End Cross Module References

// Begin Class UGPUTextureShareBlueprintLibrary Function GetActiveReceiverNames
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventGetActiveReceiverNames_Parms
	{
		TArray<FString> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Receiver" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventGetActiveReceiverNames_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "GetActiveReceiverNames", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::GPUTextureShareBlueprintLibrary_eventGetActiveReceiverNames_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::GPUTextureShareBlueprintLibrary_eventGetActiveReceiverNames_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execGetActiveReceiverNames)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FString>*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::GetActiveReceiverNames();
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function GetActiveReceiverNames

// Begin Class UGPUTextureShareBlueprintLibrary Function GetActiveSenderNames
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventGetActiveSenderNames_Parms
	{
		TArray<FString> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Sender" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventGetActiveSenderNames_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "GetActiveSenderNames", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::GPUTextureShareBlueprintLibrary_eventGetActiveSenderNames_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::GPUTextureShareBlueprintLibrary_eventGetActiveSenderNames_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execGetActiveSenderNames)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FString>*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::GetActiveSenderNames();
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function GetActiveSenderNames

// Begin Class UGPUTextureShareBlueprintLibrary Function GetLastError
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventGetLastError_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Receiver" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventGetLastError_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "GetLastError", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::GPUTextureShareBlueprintLibrary_eventGetLastError_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::GPUTextureShareBlueprintLibrary_eventGetLastError_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execGetLastError)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::GetLastError();
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function GetLastError

// Begin Class UGPUTextureShareBlueprintLibrary Function GetLastErrorByName
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventGetLastErrorByName_Parms
	{
		FString SharedName;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Receiver" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SharedName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::NewProp_SharedName = { "SharedName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventGetLastErrorByName_Parms, SharedName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedName_MetaData), NewProp_SharedName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventGetLastErrorByName_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::NewProp_SharedName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "GetLastErrorByName", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::GPUTextureShareBlueprintLibrary_eventGetLastErrorByName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::GPUTextureShareBlueprintLibrary_eventGetLastErrorByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execGetLastErrorByName)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SharedName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::GetLastErrorByName(Z_Param_SharedName);
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function GetLastErrorByName

// Begin Class UGPUTextureShareBlueprintLibrary Function GetSenderLastError
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventGetSenderLastError_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Sender" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventGetSenderLastError_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "GetSenderLastError", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::GPUTextureShareBlueprintLibrary_eventGetSenderLastError_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::GPUTextureShareBlueprintLibrary_eventGetSenderLastError_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execGetSenderLastError)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::GetSenderLastError();
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function GetSenderLastError

// Begin Class UGPUTextureShareBlueprintLibrary Function GetSenderLastErrorByName
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventGetSenderLastErrorByName_Parms
	{
		FString SharedName;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Sender" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SharedName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::NewProp_SharedName = { "SharedName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventGetSenderLastErrorByName_Parms, SharedName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedName_MetaData), NewProp_SharedName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventGetSenderLastErrorByName_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::NewProp_SharedName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "GetSenderLastErrorByName", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::GPUTextureShareBlueprintLibrary_eventGetSenderLastErrorByName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::GPUTextureShareBlueprintLibrary_eventGetSenderLastErrorByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execGetSenderLastErrorByName)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SharedName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::GetSenderLastErrorByName(Z_Param_SharedName);
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function GetSenderLastErrorByName

// Begin Class UGPUTextureShareBlueprintLibrary Function IsReceiving
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventIsReceiving_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Receiver" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GPUTextureShareBlueprintLibrary_eventIsReceiving_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GPUTextureShareBlueprintLibrary_eventIsReceiving_Parms), &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "IsReceiving", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::GPUTextureShareBlueprintLibrary_eventIsReceiving_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::GPUTextureShareBlueprintLibrary_eventIsReceiving_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execIsReceiving)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::IsReceiving();
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function IsReceiving

// Begin Class UGPUTextureShareBlueprintLibrary Function IsReceivingByName
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventIsReceivingByName_Parms
	{
		FString SharedName;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Receiver" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SharedName;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::NewProp_SharedName = { "SharedName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventIsReceivingByName_Parms, SharedName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedName_MetaData), NewProp_SharedName_MetaData) };
void Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GPUTextureShareBlueprintLibrary_eventIsReceivingByName_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GPUTextureShareBlueprintLibrary_eventIsReceivingByName_Parms), &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::NewProp_SharedName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "IsReceivingByName", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::GPUTextureShareBlueprintLibrary_eventIsReceivingByName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::GPUTextureShareBlueprintLibrary_eventIsReceivingByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execIsReceivingByName)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SharedName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::IsReceivingByName(Z_Param_SharedName);
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function IsReceivingByName

// Begin Class UGPUTextureShareBlueprintLibrary Function IsSending
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventIsSending_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Sender" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GPUTextureShareBlueprintLibrary_eventIsSending_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GPUTextureShareBlueprintLibrary_eventIsSending_Parms), &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "IsSending", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::GPUTextureShareBlueprintLibrary_eventIsSending_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::GPUTextureShareBlueprintLibrary_eventIsSending_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execIsSending)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::IsSending();
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function IsSending

// Begin Class UGPUTextureShareBlueprintLibrary Function IsSendingByName
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventIsSendingByName_Parms
	{
		FString SharedName;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Sender" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SharedName;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::NewProp_SharedName = { "SharedName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventIsSendingByName_Parms, SharedName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedName_MetaData), NewProp_SharedName_MetaData) };
void Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GPUTextureShareBlueprintLibrary_eventIsSendingByName_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GPUTextureShareBlueprintLibrary_eventIsSendingByName_Parms), &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::NewProp_SharedName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "IsSendingByName", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::GPUTextureShareBlueprintLibrary_eventIsSendingByName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::GPUTextureShareBlueprintLibrary_eventIsSendingByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execIsSendingByName)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SharedName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::IsSendingByName(Z_Param_SharedName);
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function IsSendingByName

// Begin Class UGPUTextureShareBlueprintLibrary Function StartReceiver
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventStartReceiver_Parms
	{
		FString SharedName;
		UTextureRenderTarget2D* TargetRenderTarget;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Receiver" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SharedName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetRenderTarget;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::NewProp_SharedName = { "SharedName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventStartReceiver_Parms, SharedName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedName_MetaData), NewProp_SharedName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::NewProp_TargetRenderTarget = { "TargetRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventStartReceiver_Parms, TargetRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GPUTextureShareBlueprintLibrary_eventStartReceiver_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GPUTextureShareBlueprintLibrary_eventStartReceiver_Parms), &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::NewProp_SharedName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::NewProp_TargetRenderTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "StartReceiver", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::GPUTextureShareBlueprintLibrary_eventStartReceiver_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::GPUTextureShareBlueprintLibrary_eventStartReceiver_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execStartReceiver)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SharedName);
	P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_TargetRenderTarget);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::StartReceiver(Z_Param_SharedName,Z_Param_TargetRenderTarget);
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function StartReceiver

// Begin Class UGPUTextureShareBlueprintLibrary Function StartSender
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventStartSender_Parms
	{
		FString SharedName;
		UTextureRenderTarget2D* SourceRenderTarget;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Sender" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SharedName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SourceRenderTarget;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::NewProp_SharedName = { "SharedName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventStartSender_Parms, SharedName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedName_MetaData), NewProp_SharedName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::NewProp_SourceRenderTarget = { "SourceRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventStartSender_Parms, SourceRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GPUTextureShareBlueprintLibrary_eventStartSender_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GPUTextureShareBlueprintLibrary_eventStartSender_Parms), &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::NewProp_SharedName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::NewProp_SourceRenderTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "StartSender", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::GPUTextureShareBlueprintLibrary_eventStartSender_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::GPUTextureShareBlueprintLibrary_eventStartSender_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execStartSender)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SharedName);
	P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_SourceRenderTarget);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::StartSender(Z_Param_SharedName,Z_Param_SourceRenderTarget);
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function StartSender

// Begin Class UGPUTextureShareBlueprintLibrary Function StopReceiver
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiver_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Receiver" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiver_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "StopReceiver", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiver_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiver_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiver()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiver_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execStopReceiver)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	UGPUTextureShareBlueprintLibrary::StopReceiver();
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function StopReceiver

// Begin Class UGPUTextureShareBlueprintLibrary Function StopReceiverByName
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventStopReceiverByName_Parms
	{
		FString SharedName;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Receiver" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SharedName;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::NewProp_SharedName = { "SharedName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventStopReceiverByName_Parms, SharedName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedName_MetaData), NewProp_SharedName_MetaData) };
void Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GPUTextureShareBlueprintLibrary_eventStopReceiverByName_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GPUTextureShareBlueprintLibrary_eventStopReceiverByName_Parms), &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::NewProp_SharedName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "StopReceiverByName", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::GPUTextureShareBlueprintLibrary_eventStopReceiverByName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::GPUTextureShareBlueprintLibrary_eventStopReceiverByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execStopReceiverByName)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SharedName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::StopReceiverByName(Z_Param_SharedName);
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function StopReceiverByName

// Begin Class UGPUTextureShareBlueprintLibrary Function StopSender
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSender_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Sender" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSender_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "StopSender", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSender_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSender_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSender()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSender_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execStopSender)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	UGPUTextureShareBlueprintLibrary::StopSender();
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function StopSender

// Begin Class UGPUTextureShareBlueprintLibrary Function StopSenderByName
struct Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics
{
	struct GPUTextureShareBlueprintLibrary_eventStopSenderByName_Parms
	{
		FString SharedName;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPUTextureShare|Sender" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SharedName;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::NewProp_SharedName = { "SharedName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GPUTextureShareBlueprintLibrary_eventStopSenderByName_Parms, SharedName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedName_MetaData), NewProp_SharedName_MetaData) };
void Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GPUTextureShareBlueprintLibrary_eventStopSenderByName_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GPUTextureShareBlueprintLibrary_eventStopSenderByName_Parms), &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::NewProp_SharedName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, nullptr, "StopSenderByName", nullptr, nullptr, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::GPUTextureShareBlueprintLibrary_eventStopSenderByName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::GPUTextureShareBlueprintLibrary_eventStopSenderByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGPUTextureShareBlueprintLibrary::execStopSenderByName)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SharedName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGPUTextureShareBlueprintLibrary::StopSenderByName(Z_Param_SharedName);
	P_NATIVE_END;
}
// End Class UGPUTextureShareBlueprintLibrary Function StopSenderByName

// Begin Class UGPUTextureShareBlueprintLibrary
void UGPUTextureShareBlueprintLibrary::StaticRegisterNativesUGPUTextureShareBlueprintLibrary()
{
	UClass* Class = UGPUTextureShareBlueprintLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetActiveReceiverNames", &UGPUTextureShareBlueprintLibrary::execGetActiveReceiverNames },
		{ "GetActiveSenderNames", &UGPUTextureShareBlueprintLibrary::execGetActiveSenderNames },
		{ "GetLastError", &UGPUTextureShareBlueprintLibrary::execGetLastError },
		{ "GetLastErrorByName", &UGPUTextureShareBlueprintLibrary::execGetLastErrorByName },
		{ "GetSenderLastError", &UGPUTextureShareBlueprintLibrary::execGetSenderLastError },
		{ "GetSenderLastErrorByName", &UGPUTextureShareBlueprintLibrary::execGetSenderLastErrorByName },
		{ "IsReceiving", &UGPUTextureShareBlueprintLibrary::execIsReceiving },
		{ "IsReceivingByName", &UGPUTextureShareBlueprintLibrary::execIsReceivingByName },
		{ "IsSending", &UGPUTextureShareBlueprintLibrary::execIsSending },
		{ "IsSendingByName", &UGPUTextureShareBlueprintLibrary::execIsSendingByName },
		{ "StartReceiver", &UGPUTextureShareBlueprintLibrary::execStartReceiver },
		{ "StartSender", &UGPUTextureShareBlueprintLibrary::execStartSender },
		{ "StopReceiver", &UGPUTextureShareBlueprintLibrary::execStopReceiver },
		{ "StopReceiverByName", &UGPUTextureShareBlueprintLibrary::execStopReceiverByName },
		{ "StopSender", &UGPUTextureShareBlueprintLibrary::execStopSender },
		{ "StopSenderByName", &UGPUTextureShareBlueprintLibrary::execStopSenderByName },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGPUTextureShareBlueprintLibrary);
UClass* Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_NoRegister()
{
	return UGPUTextureShareBlueprintLibrary::StaticClass();
}
struct Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "GPUTextureShareBlueprintLibrary.h" },
		{ "ModuleRelativePath", "Public/GPUTextureShareBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveReceiverNames, "GetActiveReceiverNames" }, // 3698673076
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetActiveSenderNames, "GetActiveSenderNames" }, // 1452624613
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastError, "GetLastError" }, // 3016161264
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetLastErrorByName, "GetLastErrorByName" }, // 452795476
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastError, "GetSenderLastError" }, // 1638490668
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_GetSenderLastErrorByName, "GetSenderLastErrorByName" }, // 412218439
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceiving, "IsReceiving" }, // 1365089260
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsReceivingByName, "IsReceivingByName" }, // 1518413396
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSending, "IsSending" }, // 1614499925
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_IsSendingByName, "IsSendingByName" }, // 850536987
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartReceiver, "StartReceiver" }, // 4200989742
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StartSender, "StartSender" }, // 1625790133
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiver, "StopReceiver" }, // 2730550196
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopReceiverByName, "StopReceiverByName" }, // 4237002409
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSender, "StopSender" }, // 2036158888
		{ &Z_Construct_UFunction_UGPUTextureShareBlueprintLibrary_StopSenderByName, "StopSenderByName" }, // 3227961210
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGPUTextureShareBlueprintLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_GPUTextureShare,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_Statics::ClassParams = {
	&UGPUTextureShareBlueprintLibrary::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGPUTextureShareBlueprintLibrary()
{
	if (!Z_Registration_Info_UClass_UGPUTextureShareBlueprintLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGPUTextureShareBlueprintLibrary.OuterSingleton, Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGPUTextureShareBlueprintLibrary.OuterSingleton;
}
template<> GPUTEXTURESHARE_API UClass* StaticClass<UGPUTextureShareBlueprintLibrary>()
{
	return UGPUTextureShareBlueprintLibrary::StaticClass();
}
UGPUTextureShareBlueprintLibrary::UGPUTextureShareBlueprintLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGPUTextureShareBlueprintLibrary);
UGPUTextureShareBlueprintLibrary::~UGPUTextureShareBlueprintLibrary() {}
// End Class UGPUTextureShareBlueprintLibrary

// Begin Registration
struct Z_CompiledInDeferFile_FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGPUTextureShareBlueprintLibrary, UGPUTextureShareBlueprintLibrary::StaticClass, TEXT("UGPUTextureShareBlueprintLibrary"), &Z_Registration_Info_UClass_UGPUTextureShareBlueprintLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGPUTextureShareBlueprintLibrary), 1401585972U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_3743297318(TEXT("/Script/GPUTextureShare"),
	Z_CompiledInDeferFile_FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
