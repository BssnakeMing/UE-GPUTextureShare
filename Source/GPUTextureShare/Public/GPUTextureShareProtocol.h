#pragma once

#include "CoreMinimal.h"

namespace GPUTextureShareProtocol
{
	static constexpr uint32 Magic = 0x58545357u; // "WSTX"
	static constexpr uint32 Version = 1u;
	static constexpr uint64 LegacyHeaderTagBase = 0x0000000100000000ull;

	enum class ESyncMode : uint32
	{
		None = 0,
		KeyedMutex = 1,
	};

#pragma pack(push, 1)
	struct FFrameHeaderV1
	{
		uint32 Magic = GPUTextureShareProtocol::Magic;
		uint32 Version = GPUTextureShareProtocol::Version;
		uint64 HeaderTag = 0;
		uint64 TickMs = 0;
		uint64 ProducerPid64 = 0;
		uint64 Handle = 0;
		uint32 Width = 0;
		uint32 Height = 0;
		uint32 Format = 0;
		uint32 ReservedLegacy0 = 0;
		WIDECHAR LegacyShortName[4] = {};
		WIDECHAR LegacyDisplayName[32] = {};
		ANSICHAR LegacyHandleString[32] = {};
		uint32 SyncMode = static_cast<uint32>(ESyncMode::None);
		uint32 ProducerPid = 0;
		uint64 FrameId = 0;
		uint64 Generation = 0;
		uint64 TimestampCycles64 = 0;
		uint64 LegacySharedHandle = 0;
		uint8 Reserved[64] = {};
	};
#pragma pack(pop)

	static_assert(STRUCT_OFFSET(FFrameHeaderV1, Handle) == 32, "Legacy handle offset must match TextureShareCommon.h.");
	static_assert(STRUCT_OFFSET(FFrameHeaderV1, LegacyHandleString) == 128, "Legacy handle string offset must match TextureShareCommon.h.");
}
