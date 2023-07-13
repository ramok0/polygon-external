#pragma once
#include <stdint.h>
#include <polygon.hpp>
#include <objects.h>
#include <ue4structs.hpp>

#define UNIQUE_VARAIBLE_NAME(base) base

#define ONCE_GET_OFFSET(className, propertyName, seed) \
	static std::once_flag UNIQUE_VARAIBLE_NAME(flag##seed); \
	static uint64_t UNIQUE_VARAIBLE_NAME(seed); \
	std::call_once(UNIQUE_VARAIBLE_NAME(flag##seed), []() { \
		UNIQUE_VARAIBLE_NAME(seed) = get_offset(className, propertyName);	\
		});

#define SIMPLE_READ_PTR(retType, className, propertyName, seed) \
	if(this == nullptr) return nullptr; \
	ONCE_GET_OFFSET(className, propertyName, seed##Offset); \
	if(!seed##Offset) return nullptr; \
	RPM(retType, (uintptr_t)this + seed##Offset, seed##Ptr); \
	if(!seed##Ptr##Success) return nullptr; \
	return seed##Ptr;
		
inline std::unordered_map<std::string, std::unordered_map<std::string, int32_t>> offset_cache;

constexpr float BOX_REDUCTION_FACTOR = 0.380f;

class AItem_Gun_General {
public:
	float get_time_between_shots(void);
};

class UInventoryComponent_Game {
public:
	AItem_Gun_General* get_current_weapon();
};

class USceneComponent {
public:
	Vector3 relative_location(void);
	FBoxSphereBounds get_cached_bounds(void);
};

class AActor {
public:
	USceneComponent* get_root_component(void);
};

class UGameInstance {
public:
	class ULocalPlayer* get_local_player(void);
};

class AGameState {
public:
	std::optional<TArray<class APlayerState*>> get_player_array(void);
};

class UWorld {
public:
	class UGameInstance* get_game_instance(void);
	class AGameState* get_game_state(void);
};

class APlayerState {
public:
	class APawn* get_pawn();
	uint8_t get_team_number(void);
	std::string get_player_name(void);
	UInventoryComponent_Game* get_inventory(void);
};

class USkinnedAsset {
public:
	std::unordered_map <std::string, int> get_bones();
};

class USkeletalMeshComponent {
public:
	std::optional<TArray<FTransform>> get_bone_array(void);
	std::unique_ptr<FTransform> get_bones(void);
	Vector3 get_bone_with_rotation(FTransform bone);
	FTransform get_component_to_world(void);
	USkinnedAsset* get_skinned_asset(void);
};

struct HealthStatsComponentData {
	uint8_t Health;
	bool bIsAlive;
	bool bHealthProtection;
	float LastTimeTakeDamage;
	float Stamina;
};

class UHealthStatsComponent {
public:
	std::optional<HealthStatsComponentData> get_data();
};

class APawn {
public:
	USkeletalMeshComponent* get_mesh(void);
	UHealthStatsComponent* get_health_component(void);
	APlayerState* get_player_state(void);
};

class APlayerCameraManager {
public:
	std::optional<FMinimalViewInfo> get_camera(void);
};

class APlayerController {
public:
	class APawn* get_pawn(void);
	class APlayerCameraManager* get_camera_manager(void);
};

class ULocalPlayer {
public:
	class APlayerController* get_player_controller(void);
};

Vector2Float world_to_screen(Vector3 world_location);

void cache_offsets(void);
uint64_t get_offset(std::string ClassName, std::string PropertyName);
UWorld* get_world(void);


namespace overlay {
	void draw_tracers(void);
	void draw_2d_bounding_esp(USceneComponent* RootComponent);
	void draw_2d_corner(USkeletalMeshComponent* Mesh);
	void draw_2d(USkeletalMeshComponent* Mesh);
	void draw3d_esp(USceneComponent* RootComponent);
	void draw_player_name(USkeletalMeshComponent* Mesh, std::string player_name);

	void draw(void);
}

namespace exploits {
	void infinite_stamina(void);
	void rapid_fire();
	void no_spread(void);
	void no_recoil(void);
	void instantaim();
	float get_original_time_between_shots(void);
}