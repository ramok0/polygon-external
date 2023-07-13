#include <cache.hpp>
#include <polygon.hpp>
#include <game.hpp>
#include <ue4.hpp>
#include <iostream>

void cache::cache_data()
{
	int count = 0;
	auto start = std::chrono::high_resolution_clock::now();
	while (true) {
		UWorld* World = get_world();
		if (!World) FAIL_CONTINUE("World");

		APlayerController* LocalPlayerController = World->get_game_instance()->get_local_player()->get_player_controller();

		if (!LocalPlayerController) FAIL_CONTINUE("LocalPlayerController");

		cache::LocalController = LocalPlayerController;

		std::optional<FMinimalViewInfo> camera = LocalPlayerController->get_camera_manager()->get_camera();
		if (!camera) FAIL_CONTINUE("get_camera");

		cache::view_info = *camera;

		APawn* LocalPawn = LocalPlayerController->get_pawn();
		if (!LocalPawn) FAIL_CONTINUE("LocalPawn");

		APlayerState* LocalPlayerState = LocalPawn->get_player_state();

		cache::LocalPawn = LocalPawn;
		cache::LocalTeam = LocalPlayerState->get_team_number();

		cache::LocalHealthStatsComponent = LocalPawn->get_health_component();
		cache::LocalCurrentWeapon = LocalPlayerState->get_inventory()->get_current_weapon();

		//cache players
		std::optional<TArray<APlayerState*>> playerList = World->get_game_state()->get_player_array();
		if (!playerList || (*playerList).Count == 1) FAIL_CONTINUE("playerList");

		std::vector<Entity_t> temp_entities;

		for (int i = 0; i < (*playerList).Count; i++)
		{
			APlayerState* playerState = (*playerList)[i];
			APawn* pawn = playerState->get_pawn();
			if (!pawn || pawn == LocalPawn) continue;

			USkeletalMeshComponent* mesh = pawn->get_mesh();
			if (!mesh) continue;

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
			entity.player_name = playerState->get_player_name();
			entity.bones = mesh->get_bones();

			temp_entities.push_back(entity);
		}

		cache::entities = temp_entities;
		count++;

		auto end = std::chrono::high_resolution_clock::now();

		float elapsedSeconds = std::chrono::duration<float>(end-start).count();

		data::cache_per_second = count / elapsedSeconds;

		exploits::infinite_stamina();
		exploits::rapid_fire();
		exploits::instantaim();
		exploits::no_recoil();
		exploits::no_spread();

	//	Sleep(1000 / 300);
	}
}