#pragma once

#include <libconfig.hpp>
#include <ressources/window_constants.h>
#include <game.hpp>

#define RPM(type, address, varName) auto [varName, varName##Success] = driver::read<type>(address);

namespace data {
	inline bool menu_open;
	inline HWND gameWindow;
	inline HWND myWindow;
	inline int Width;
	inline int Height;
	inline double DeltaTime;
	inline long long LastFrameTimeStamp;
	inline unsigned long pid;
	inline HANDLE driver_handle;
	inline unsigned long long base_address;
	inline float ScreenCenterX;
	inline float ScreenCenterY;
	inline WINDOW_TABS current_tab;
	inline float cache_per_second;
	inline float world_to_meters;
}

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
	};

	inline libconfig::ConfigurationLoader<config_t>* config = new libconfig::ConfigurationLoader<config_t>("polygon");
	
	bool init(void);
}

namespace window {
	bool create(GLFWwindow** lpWindow);
	bool setup(GLFWwindow* window);
	ImVec4 convert_color(const std::string& codeCouleurHTML);
	void tick(GLFWwindow* window);
	void cleanup(GLFWwindow* window);
}

ImColor get_color_from_float_array(float* color);

namespace driver {
	bool init(void);
	uint64_t get_base_address(void);
	bool read(uintptr_t address, uintptr_t buffer, uintptr_t size);
	bool write(uintptr_t address, uintptr_t buffer, uintptr_t size);
	template <typename T> std::tuple<T, bool> read(uintptr_t address)
	{
		T buf;
		if (address == 0) {
			return { buf, false};
		}

		bool success = read(address, (uintptr_t)&buf, sizeof(T));
		if(!success) {
			return { buf, false };
		}

		return { buf, true };
	}

	template <typename T> T unsafe_read(uintptr_t address) {
		if (!address) {
			return T{ 0 };
		}

		T buf;

		bool success = driver::read(address, (uintptr_t)&buf, sizeof(T));

		if (!success) {
			return T{ 0 };
		}

		return buf;
	}

	template <typename T> bool write(uintptr_t address, T buffer)
	{
		return write(address, (uintptr_t)&buffer, sizeof(T));
	}
}

namespace gui {
	void draw_tabs(void);
	void draw_menu(void);
}