#include <ue4.hpp>
#include <cache.hpp>

void overlay::draw(void) {
	config::config_t* data = config::config->data();
	for (auto& entity : cache::entities) {
		if (entity.HealthComponentData.bIsAlive == false || entity.HealthComponentData.Health == 0) continue;
		if (data->team_check && cache::LocalTeam == entity.Team) continue;

		FTransform* bones = entity.bones.get();

		switch (data->esp_mode) {
		case ESP_MODE::ESP_3D:
			overlay::draw3d_esp(entity.RootComponent);
			break;
		case ESP_MODE::ESP_2DCORNER:
			overlay::draw_2d_corner(entity.Mesh, bones);
			break;
		case ESP_MODE::ESP_2D:
			overlay::draw_2d(entity.Mesh, bones);
			break;	
		default:
		case ESP_MODE::ESP_2DBOUNDING:
			overlay::draw_2d_bounding_esp(entity.RootComponent);
			break;
		}
		
		if (data->esp_player_name) {
			overlay::draw_player_name(entity.Mesh, bones, entity.player_name);
		}

		//overlay::draw3d_esp(entity.RootComponent);
	}

	if (data->debug_info) {
		ImGui::GetForegroundDrawList()->AddText({ 30.f, 30.f }, ImColor(255, 0, 0), std::format("Render FPS : {}\nCache Per Second : {}", ImGui::GetIO().Framerate, data::cache_per_second).c_str());
	}
}