#pragma once
#include <stdint.h>
#include <optional>
#include <vectortypes.h>
#include <gamestructs.h>
#include <ue4.h>

typedef unsigned char uint8_t;

class UHealthStatsComponent {
public:
	std::optional<HealthStatsComponentData> get_data();
	bool set_stamina(float data);
};

class APawn {
public:
	class USkeletalMeshComponent* get_mesh(void);
	class UHealthStatsComponent* get_health_component(void);
	class APlayerState* get_player_state(void);

	bool move_at(FRotator look_at_coords);
};

class APlayerCameraManager {
public:
	std::optional<FMinimalViewInfo> get_camera(void);
};

class APlayerController {
public:
	class APawn* get_pawn(void);
	class APlayerCameraManager* get_camera_manager(void);
	FRotator get_control_rotation(void);
};

class ULocalPlayer {
public:
	class APlayerController* get_player_controller(void);
};

class AItem_Gun_General {
public:
	float get_time_between_shots(void);
	float get_mobility(void);
	FText get_text(void);
	bool set_air_down_time_multiplier(float value);
	bool set_recoil(float uprecoil, float backwardrecoil, float gunrecoilalphapershot, float gunrecoillift);
	bool set_spread(float current_spread, float spread_shot);
	bool set_mobility(float mobility);
	bool set_fire_rate(float rate);
	bool set_reload_animations(void* ReloadCharacterAnimation, void* ReloadFullCharacterAnimation, void* ReloadGunAnimation, void* ReloadFullGunAnimation);
	bool set_equip_animation(void* Animation);

	float get_air_down_time_multiplier(void);
	RecoilStruct get_recoil(void);
	SpreadData get_spread(void);
	ReloadAnimations get_reload_animations(void);
};

class UInventoryComponent_Game {
public:
	AItem_Gun_General* get_current_weapon();
	AItem_Gun_General* get_primary_weapon();
	AItem_Gun_General* get_secondary_weapon();
};

class USceneComponent {
public:
	Vector3 relative_location(void);
	FBoxSphereBounds get_cached_bounds(void);
	render_info_t get_render_data(void);
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
	EPG_GameState get_game_status(void);
};

class AWorldSettings {
public:
	float get_world_to_meters(void);
};

class ULevel {
public:
	class AWorldSettings* get_world_settings(void);
};

class UWorld {
public:
	class UGameInstance* get_game_instance(void);
	class AGameState* get_game_state(void);
	class ULevel* get_persistent_level(void);
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
	std::vector <std::string> get_bones_as_vector();
};

class USkeletalMeshComponent {
public:
	std::optional<TArray<FTransform>> get_bone_array(void);
	//std::shared_ptr<FTransform[]> get_bones(size_t* size);
	Vector3 get_bone_with_rotation(int Index);
	FTransform get_component_to_world(void);
	USkinnedAsset* get_skinned_asset(void);
	bool set_force_wireframe(bool new_val);
	bool was_recently_rendered(void);
};