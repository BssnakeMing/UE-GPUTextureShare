// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GPUTextureShareBlueprintLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UTextureRenderTarget2D;
#ifdef GPUTEXTURESHARE_GPUTextureShareBlueprintLibrary_generated_h
#error "GPUTextureShareBlueprintLibrary.generated.h already included, missing '#pragma once' in GPUTextureShareBlueprintLibrary.h"
#endif
#define GPUTEXTURESHARE_GPUTextureShareBlueprintLibrary_generated_h

#define FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetActiveReceiverNames); \
	DECLARE_FUNCTION(execGetLastErrorByName); \
	DECLARE_FUNCTION(execGetLastError); \
	DECLARE_FUNCTION(execIsReceivingByName); \
	DECLARE_FUNCTION(execIsReceiving); \
	DECLARE_FUNCTION(execStopReceiverByName); \
	DECLARE_FUNCTION(execStopReceiver); \
	DECLARE_FUNCTION(execStartReceiver); \
	DECLARE_FUNCTION(execGetActiveSenderNames); \
	DECLARE_FUNCTION(execGetSenderLastErrorByName); \
	DECLARE_FUNCTION(execGetSenderLastError); \
	DECLARE_FUNCTION(execIsSendingByName); \
	DECLARE_FUNCTION(execIsSending); \
	DECLARE_FUNCTION(execStopSenderByName); \
	DECLARE_FUNCTION(execStopSender); \
	DECLARE_FUNCTION(execStartSender);


#define FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGPUTextureShareBlueprintLibrary(); \
	friend struct Z_Construct_UClass_UGPUTextureShareBlueprintLibrary_Statics; \
public: \
	DECLARE_CLASS(UGPUTextureShareBlueprintLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GPUTextureShare"), NO_API) \
	DECLARE_SERIALIZER(UGPUTextureShareBlueprintLibrary)


#define FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGPUTextureShareBlueprintLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UGPUTextureShareBlueprintLibrary(UGPUTextureShareBlueprintLibrary&&); \
	UGPUTextureShareBlueprintLibrary(const UGPUTextureShareBlueprintLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGPUTextureShareBlueprintLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGPUTextureShareBlueprintLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGPUTextureShareBlueprintLibrary) \
	NO_API virtual ~UGPUTextureShareBlueprintLibrary();


#define FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_11_PROLOG
#define FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_14_INCLASS_NO_PURE_DECLS \
	FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GPUTEXTURESHARE_API UClass* StaticClass<class UGPUTextureShareBlueprintLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pack_Plugins_GPUTextureShare_HostProject_Plugins_GPUTextureShare_Source_GPUTextureShare_Public_GPUTextureShareBlueprintLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
