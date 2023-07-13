#pragma once
#include <ue4.hpp>

#define FAIL_CONTINUE(obj){\
		printf("failed to process " obj "\n"); \
		continue;\
	}

struct Entity_t {
	APawn* Pawn;
	USceneComponent* RootComponent;
	APlayerState* PlayerState;
	USkeletalMeshComponent* Mesh;
	HealthStatsComponentData HealthComponentData;
	uint8_t Team;
	std::string player_name;
	std::shared_ptr<FTransform> bones;
};

namespace cache {
	inline uint8_t GameStatus;
	inline APlayerController* LocalController;
	inline APawn* LocalPawn;
	inline FMinimalViewInfo view_info;
	inline std::vector<Entity_t> entities;
	inline uint8_t LocalTeam;
	inline UHealthStatsComponent* LocalHealthStatsComponent;
	inline AItem_Gun_General* LocalCurrentWeapon;
	//inline std::unordered_map<std::string, std::unordered_map <std::string, int>> skeleton_name_to_bone_name_to_id;

	void cache_data();
}