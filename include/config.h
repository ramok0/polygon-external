#pragma once
#include <libconfig.hpp>
#include <menu_structures.h>

namespace config {
	struct config_t {
		bool vsync;
		bool esp;
		bool smoothing;
		float smoothing_value;
		bool team_check;
		ESP_MODE esp_mode;
		bool esp_filled;
		float esp_filled_color[4];
		float esp_color[4];
		bool vis_check;
		bool aim;
		bool fov;
		int fov_value;
		bool esp_player_name;
		float esp_player_name_color[4];
		bool debug_info;
		bool no_spread;
		bool no_recoil;
		bool infinite_stamina;
		bool rapid_fire;
		bool fast_move;
		float time_between_shots;
		bool instant_aim;
		bool skeleton_esp;
		float skeleton_esp_color[4];
		float skeleton_thickness;
		float fov_circle_color[4];
		bool aim_tracer;
		float esp_visible_color[4];
		int aim_bone;
		bool wireframe;
		bool esp_player_weapon;
		bool esp_health_box;
		bool esp_health_text;
		bool esp_skeleton_bezier;
		bool esp_skeleton_full;
		int num_of_bezier_segments;
		bool instant_reload;
		int tracers_bone;
		bool tracers;
	};

	inline libconfig::ConfigurationLoader<config_t>* config = new libconfig::ConfigurationLoader<config_t>("polygon");

	bool init(void);
}