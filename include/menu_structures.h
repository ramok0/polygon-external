#pragma once
#include <cstdint>

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

static const char* esp_mode_to_string[5] = {
	"3D",
	"2D",
	"2D Light",
	"2D Cornered",
	"ESP_MAX???"
};