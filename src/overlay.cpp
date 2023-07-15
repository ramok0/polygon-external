#include <ue4.hpp>
#include <overlay.hpp>

void overlay::draw(void) {
	config::config_t* data = config::config->data();
	for (auto& entity : cache::entities) {
		if (entity.HealthComponentData.bIsAlive == false || entity.HealthComponentData.Health == 0) continue;
		if (data->team_check && cache::LocalTeam == entity.Team) continue;

		//Vector3 loc = entity.Mesh->get_bone_with_rotation(8);
		//auto screen = world_to_screen(loc);

		//ImGui::GetBackgroundDrawList()->AddLine({ 0.f, 0.f }, { screen.x, screen.y }, ImColor(255, 0, 0));

		overlay::esp::get_method()(entity);

		if (data->skeleton_esp)
			overlay::esp::draw_skeleton(entity);
		
		if (data->esp_player_name)
			overlay::esp::draw_player_name(entity);
	}

	if (data->debug_info) {
		ImGui::GetForegroundDrawList()->AddText({ 30.f, 30.f }, ImColor(255, 0, 0), std::format("Render FPS : {}\nCache Per Second : {}", ImGui::GetIO().Framerate, data::cache_per_second).c_str());
	}
}