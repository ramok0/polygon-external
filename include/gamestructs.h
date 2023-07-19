#pragma once
#include <names.h>
#include <vectortypes.h>
#include <tarray.h>

#include <cstdint>
#include <vector>
#include <memory>

enum class EPG_GameState : uint8_t {
	NONE = 0,
	WAITING_PLAYERS = 1,
	PAUSE = 2,
	COUNTDOWN = 3,
	GAME = 4,
	ENDED = 5,
	EPG_MAX = 6
};

struct BoneArray {
	TArray<FTransform> ComponentSpaceTransformsArray[2];
};

struct FMeshBoneInfo
{
	// Bone's name.
	FName Name;

	// INDEX_NONE if this is the root bone. 
	int32_t ParentIndex;
};

struct FBoxSphereBounds {
	struct Vector3 Origin; // 0x00(0x18)
	struct Vector3 BoxExtent; // 0x18(0x18)
	double SphereRadius; // 0x30(0x08)
};

struct FTextData {
	char pad[0x40];
	FString string;
};

struct FText {
	void* VTable;
	FTextData* Data;

	operator bool() {
		return Data != nullptr;
	}

	std::string get_string(void);
};