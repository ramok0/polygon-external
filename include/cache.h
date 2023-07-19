#pragma once
#include <vectortypes.h>
#include <bonecluster.h>
#include <ue4.h>
#include <gamestructs.h>

#include <string>
#include <vector>
#include <optional>

#define FAIL_CONTINUE(obj){\
		continue;\
	}

class APawn;
class USceneComponent;
class USkeletalMeshComponent;
class APlayerController;
class UHealthStatsComponent;
class AItem_Gun_General;
class UInventoryComponent_Game;
class APlayerState;

struct Entity_t {

	APawn* Pawn;
	USceneComponent* RootComponent;
	APlayerState* PlayerState;
	USkeletalMeshComponent* Mesh;
	HealthStatsComponentData HealthComponentData;
	uint8_t Team;
	float Distance;
	std::string player_name;
	BoneCluster player_bones;
	FTransform component_to_world;
	bool is_visible;
	int current_text_offset;
	std::string weapon_name;

	Vector3 get_bone_with_rotation(int Index)
	{
		if (Index > this->player_bones.size()) {
			return { 0 };
		}

		FTransform bone = this->player_bones[Index];
		FMatrix matrix = bone.ToMatrixWithScale() * component_to_world.ToMatrixWithScale();

		return Vector3(matrix.M[3][0], matrix.M[3][1], matrix.M[3][2]);
	}
};

namespace cache {
	inline EPG_GameState GameStatus;
	inline APlayerController* LocalController;
	inline APawn* LocalPawn;
	inline FMinimalViewInfo view_info;
	inline std::vector<Entity_t> entities;
	inline 	APlayerState* LocalPlayerState;
	inline uint8_t LocalTeam;
	inline UHealthStatsComponent* LocalHealthStatsComponent;
	inline AItem_Gun_General* LocalCurrentWeapon;
	inline UInventoryComponent_Game* LocalInventory;
	inline float world_to_meters;
	inline std::optional<Entity_t> closest_entity;
	inline std::vector<std::string> bones;
	//inline std::unordered_map<std::string, std::unordered_map <std::string, int>> skeleton_name_to_bone_name_to_id;

	void cache_data();
}