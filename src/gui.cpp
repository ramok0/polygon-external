#include <polygon.h>
#include <cache.h>
#include <config.h>
#include <exploits.h>
#include <window.h>
#include <imhelper.h>

void gui::draw_tabs(void)
{
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, BUTTON_SIZE + 20.f);
	ImVec2 button_size = ImVec2(BUTTON_SIZE, 40);

	if (center_tab_button("Aimbot", button_size))
		data::current_tab = WINDOW_TABS::AIMBOT;

	if (center_tab_button("ESP", button_size))
		data::current_tab = WINDOW_TABS::ESP;	
	
	if (center_tab_button("Tracers", button_size))
		data::current_tab = WINDOW_TABS::Tracers;

	if (center_tab_button("Extras", button_size))
		data::current_tab = WINDOW_TABS::EXTRA;

	if (center_tab_button("Save Configuration", button_size))
		config::config->write();

	ImGui::NextColumn();
}

void gui::draw_menu(void)
{
	//ImGui::ShowStyleEditor();
	config::config_t* data = config::config->data();
	ImGuiIO& io = ImGui::GetIO();

	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::SetNextWindowPos(DefaultWindowPos, ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(DefaultWindowSize, ImGuiCond_Always);
	ImGui::Begin("ramokaka", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

	gui::draw_tabs();

	switch (data::current_tab) {
	case WINDOW_TABS::AIMBOT:
		text_centered("Aimbot");
		ImGui::Spacing();
		ImGui::Checkbox("Enable", &data->aim);
		ImGui::Checkbox("Smoothing", &data->smoothing);

		if (data->aim && cache::bones.size() != 0) {
			if (ImGui::BeginCombo("Aim Bone", cache::bones[data->aim_bone].c_str()))
			{
				for (int i = 0; i < cache::bones.size(); i++)
				{
					bool is_selected = data->aim_bone == i;
					if (ImGui::Selectable(cache::bones[i].c_str(), &is_selected))
					{
						data->aim_bone = i;
					}

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
		}

		if (data->smoothing)
		{
			ImGui::SliderFloat(" ", &data->smoothing_value, 0, 1, "% .2f");
		}
		ImGui::Checkbox("Enable FOV", &data->fov);
		ImGui::Checkbox("Enable closest player tracer", &data->aim_tracer);

		if (data->fov) {
			ImGui::SliderInt("Aimbot FOV", &data->fov_value, 10, 250);
			ImGui::ColorEdit4("##fov_circle_color", data->fov_circle_color, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Text("FOV Circle Color");
		}

		if (data->vis_check) {
			ImGui::ColorEdit4("##esp_vis_color", data->esp_visible_color, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Text("ESP Visible Color");
		}

		ImGui::Checkbox("Visible Check", &data->vis_check);
		ImGui::Checkbox("Team Check", &data->team_check);
		break;
	case WINDOW_TABS::ESP:
		text_centered("Visuals");
		ImGui::Spacing();

		ImGui::Checkbox("Enable ESP", &data->esp);
		ImGui::Checkbox("Enable Skeleton ESP", &data->skeleton_esp);
		ImGui::Checkbox("Enable ESP Filled", &data->esp_filled);
		ImGui::Checkbox("Enable Names ESP", &data->esp_player_name);
		ImGui::Checkbox("Enable Weapons ESP", &data->esp_player_weapon);
		ImGui::Checkbox("Enable Health ESP Boxes", &data->esp_health_box);
		ImGui::Checkbox("Enable Health ESP Text", &data->esp_health_text);
		ImGui::Checkbox("Wireframe", &data->wireframe);
		if (data->esp) {
			ImGui::ColorEdit4("##color", data->esp_color, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Text("ESP Color");
		}

		if (data->esp_filled) {
			ImGui::ColorEdit4("##filledcolor", data->esp_filled_color, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Text("ESP Filled Color");
		}	

		if (data->skeleton_esp) {
			ImGui::ColorEdit4("##skeleton_esp_color", data->skeleton_esp_color, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Text("Skeleton Color");

			ImGui::Checkbox("Full Skeleton", &data->esp_skeleton_full);
			ImGui::Checkbox("Bezier Skeleton", &data->esp_skeleton_bezier);
			if (data->esp_skeleton_bezier)
			{
				ImGui::SliderInt("Num Of Bezier Segments", &data->num_of_bezier_segments, 2, 32);
			}
			ImGui::SliderFloat("Skeleton Thickness", &data->skeleton_thickness, 0.2f, 2.5f);
		}
		
		if (data->esp_player_name) {
			ImGui::ColorEdit4("##namescolor", data->esp_player_name_color, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Text("ESP Player Name Color");
		}

		if (data->esp_mode > ESP_MAX) {
			data->esp_mode = ESP_3D;
			config::config->write();
		}
		ImGui::SliderInt("ESP Mode", (int*)&data->esp_mode, ESP_3D, ESP_MAX-1, (const char*)esp_mode_to_string[data->esp_mode]);

		ImGui::Checkbox("Visible Check", &data->vis_check);
		ImGui::Checkbox("Team Check", &data->team_check);

		break;
	case WINDOW_TABS::Tracers:
		text_centered("Tracers");
		ImGui::Spacing();

		ImGui::Checkbox("Enable Tracers", &data->tracers);

		if (data->tracers && cache::bones.size() != 0) {
			if (ImGui::BeginCombo("Tracers Bone", cache::bones[data->tracers_bone].c_str()))
			{
				for (int i = 0; i < cache::bones.size(); i++)
				{
					bool is_selected = data->tracers_bone == i;
					if (ImGui::Selectable(cache::bones[i].c_str(), &is_selected))
					{
						data->tracers_bone = i;
					}

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
		}

		break;
	case WINDOW_TABS::EXTRA:
		text_centered("Extra");
		ImGui::Spacing();
		ImGui::Checkbox("Debug Info", &data->debug_info);

		for (const auto& exploit : m_exploits)
		{
			ImGui::Checkbox(exploit->get_name().c_str(), exploit->get_enabled_ptr());
		}

		if (data->rapid_fire) {
			ImGui::SliderFloat("Time Between Shots", &data->time_between_shots, 0.002f, 0.35f);
		}

		ImGui::Spacing();

		ImGui::Checkbox("Module List", &config::config->data()->module_list);
		if (config::config->data()->module_list) {
			ImGui::Checkbox("RGB Module List", &config::config->data()->module_list_rgb);
		}

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Self Destruct"))
		{
			data::should_self_destruct = true;
		}

		break;
	}
	


	ImGui::End();
}