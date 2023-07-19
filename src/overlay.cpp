#include <overlay.h>
#include <config.h>
#include <cache.h>
#include <polygon.h>
#include <imhelper.h>

void overlay::draw(void) {
	config::config_t* data = config::config->data();
	for (auto& entity : cache::entities) {
		if (entity.HealthComponentData.bIsAlive == false || entity.HealthComponentData.Health == 0) continue;
		if (data->team_check && cache::LocalTeam == entity.Team) continue;

		entity.current_text_offset = 2;

		overlay::esp::get_method()(entity);

		if (data->skeleton_esp)
			overlay::esp::draw_skeleton(entity);

		if(data->esp_health_box || data->esp_health_text)
			overlay::esp::draw_health(&entity);

		if(data->esp_player_weapon)
			overlay::esp::draw_weapon_name(&entity);

		if (data->esp_player_name)
			overlay::esp::draw_player_name(&entity);
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