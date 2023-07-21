#include <cache.h>
#include <polygon.h>
#include <game.h>
#include <ue4.h>
#include <config.h>

#include <chrono>
#include <exploits.h>
#include <modules.h>
#include <wrappers.h>

void cache::cache_data()
{
	int count = 0;
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << "Starting into cache thread.." << std::endl;
	while (true) {
		UWorld* World = get_world();
		if (!World) FAIL_CONTINUE("World");

		AGameState* GameState = World->get_game_state();

		cache::GameStatus = GameState->get_game_status();

		if (cache::GameStatus != EPG_GameState::GAME) {
			cache::entities.clear();
			FAIL_CONTINUE("GameStatus");
		}


		APlayerController* LocalPlayerController = World->get_game_instance()->get_local_player()->get_player_controller();

		if (!LocalPlayerController) FAIL_CONTINUE("LocalPlayerController");

		cache::LocalController = LocalPlayerController;

		std::optional<FMinimalViewInfo> camera = LocalPlayerController->get_camera_manager()->get_camera();
		if (!camera) FAIL_CONTINUE("get_camera");

		cache::view_info = *camera;

		APawn* LocalPawn = LocalPlayerController->get_pawn();
		if (!LocalPawn) FAIL_CONTINUE("LocalPawn");

		APlayerState* LocalPlayerState = LocalPawn->get_player_state();

		cache::LocalPlayerState = LocalPlayerState;
		cache::LocalPawn = LocalPawn;
		cache::LocalTeam = LocalPlayerState->get_team_number();

		cache::LocalHealthStatsComponent = LocalPawn->get_health_component();
		cache::LocalInventory = LocalPlayerState->get_inventory();
		cache::LocalCurrentWeapon = cache::LocalInventory->get_current_weapon();

		cache::world_to_meters = World->get_persistent_level()->get_world_settings()->get_world_to_meters();

		if (cache::bones.size() == 0)
			cache::bones = LocalPawn->get_mesh()->get_skinned_asset()->get_bones_as_vector();

		//cache players
		std::optional<TArray<APlayerState*>> playerList = GameState->get_player_array();
		if (!playerList || (*playerList).Count == 1) FAIL_CONTINUE("playerList");

		std::vector<Entity_t> temp_entities;

		std::optional<Entity_t> closest_entity;
		float current_min_distance = FLT_MAX;

		for (int i = 0; i < (*playerList).Count; i++)
		{
			APlayerState* playerState = (*playerList)[i];
			APawn* pawn = playerState->get_pawn();
			if (!pawn || pawn == LocalPawn) continue;
			if (playerState == LocalPlayerState) continue;

			USkeletalMeshComponent* mesh = pawn->get_mesh();
			if (!mesh) continue;

			mesh->set_force_wireframe(config::config->data()->wireframe);

			std::optional<TArray<FTransform>> bones = mesh->get_bone_array();
			if (!bones) continue;

			std::optional<HealthStatsComponentData> healthData = pawn->get_health_component()->get_data();
			if (!healthData) continue;
			USceneComponent* rootComponent = ((AActor*)pawn)->get_root_component();
			if (!rootComponent) continue;

			Entity_t entity;

			entity.Mesh = mesh;
			entity.Pawn = pawn;
			entity.PlayerState = playerState;
			entity.RootComponent = rootComponent;
			entity.HealthComponentData = *healthData;
			entity.Team = playerState->get_team_number();
			entity.Distance = (float)cache::view_info.Location.Distance(rootComponent->relative_location());
			entity.player_name = std::format("[{}m] {}", roundf(entity.Distance / cache::world_to_meters), playerState->get_player_name());
			entity.player_bones = BoneCluster(entity.Mesh);
			entity.component_to_world = mesh->get_component_to_world();
			entity.current_text_offset = 2;
			entity.is_visible = mesh->was_recently_rendered();
			entity.weapon_name = playerState->get_inventory()->get_current_weapon()->get_text().get_string();

			if (config::config->data()->aim && (config::config->data()->vis_check ? entity.is_visible : true) && entity.Team != cache::LocalTeam && entity.HealthComponentData.bIsAlive && !entity.HealthComponentData.bHealthProtection && entity.HealthComponentData.Health != 0)
			{
				Vector3 head_position = entity.get_bone_with_rotation(Bones::Head);
				if (head_position) {
					Vector2Float screen_head_position = world_to_screen(head_position);
					if (screen_head_position)
					{
						Vector2Float center_screen = { data::ScreenCenterX, data::ScreenCenterY };
						float distance2d = center_screen.Distance(screen_head_position);
						if (current_min_distance > distance2d) {
							if (!config::config->data()->fov || config::config->data()->fov_value > distance2d) {
								closest_entity = entity;
								current_min_distance = distance2d;
							}
						}
					}
				}
			}

			temp_entities.push_back(entity);
		}

		cache::closest_entity = closest_entity;

		cache::entities = temp_entities;
		count++;

		auto end = std::chrono::high_resolution_clock::now();

		float elapsedSeconds = std::chrono::duration<float>(end - start).count();

		data::cache_per_second = count / elapsedSeconds;

		if (data::should_self_destruct)
		{
			break;
		}

		for (const auto& exploit : m_exploits) {
			exploit->tick();
		}

		modules::aimbot();

		//	Sleep(1000 / 300);
	}
}