#include <ue4.hpp>
#include <overlay.hpp>

void overlay::draw(void) {
	config::config_t* data = config::config->data();
	for (auto& entity : cache::entities) {
		if (entity.HealthComponentData.bIsAlive == false || entity.HealthComponentData.Health == 0) continue;
		if (data->team_check && cache::LocalTeam == entity.Team) continue;

	/*	Vector3 loc = entity.Mesh->get_bone_with_rotation(Bones::pelvis);
		auto screen = world_to_screen(loc);

		ImGui::GetBackgroundDrawList()->AddText({ screen.x, screen.y }, ImColor(0, 255, 0), entity.is_visible ? "1" : "0");*/

		overlay::esp::get_method()(entity);

		if (data->skeleton_esp)
			overlay::esp::draw_skeleton(entity);
		
		if (data->esp_player_name)
			overlay::esp::draw_player_name(entity);
	}

	if (data->aim && data->fov) {
		ImGui::GetBackgroundDrawList()->AddCircle({ data::ScreenCenterX, data::ScreenCenterY }, (float)data->fov_value, get_color_from_float_array(data->fov_circle_color));
		
		if (cache::closest_entity && data->aim_tracer) {
			Vector2Float head_screen_loc = world_to_screen((*cache::closest_entity).get_bone_with_rotation(data->aim_bone));
			ImGui::GetBackgroundDrawList()->AddLine({ data::ScreenCenterX, data::ScreenCenterY }, { head_screen_loc.x, head_screen_loc.y }, get_color_from_float_array(data->esp_color));
		}
	}

	if (data->debug_info) {
		ImGui::GetForegroundDrawList()->AddText({ 30.f, 30.f }, ImColor(255, 0, 0), std::format("Render FPS : {}\nCache Per Second : {}", ImGui::GetIO().Framerate, data::cache_per_second).c_str());
	}
}