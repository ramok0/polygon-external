#pragma once
#ifdef NDEBUG
#pragma comment(lib, "lib/GLFW/glfw3.lib")
#pragma comment(lib, "lib/libconfig_release.lib")
#elif _DEBUG
#pragma comment(lib, "lib/libconfig_debug.lib")
#pragma comment(lib, "lib/GLFW/glfw3debug.lib")
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <imgui/imgui.h>

const ImVec2 DefaultWindowSize = { 800.f, 600.f };
const ImVec2 DefaultWindowPos = { 10.f, 10.f };
constexpr float BUTTON_SIZE = 135.f;

enum WINDOW_TABS : uint8_t {
	AIMBOT,
	ESP,
	Tracers,
	EXTRA
};

enum ESP_MODE : int {
	ESP_3D = 0,
	ESP_2D = 1,
	ESP_2DBOUNDING = 2,
	ESP_2DCORNER = 3,
	ESP_MAX
};

static const char* esp_mode_to_string[4] = {
	"3D",
	"2D",
	"2D Light",
	"2D Cornered"
};