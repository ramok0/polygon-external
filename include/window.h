#pragma once
#pragma once
#ifdef NDEBUG
#pragma comment(lib, "lib/GLFW/glfw3.lib")
#pragma comment(lib, "lib/libconfig_release.lib")
#elif _DEBUG
#pragma comment(lib, "lib/libconfig_debug.lib")
#pragma comment(lib, "lib/GLFW/glfw3debug.lib")
#endif

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <string>

const ImVec2 DefaultWindowSize = { 800.f, 600.f };
const ImVec2 DefaultWindowPos = { 10.f, 10.f };
constexpr float BUTTON_SIZE = 135.f;

constexpr float BOX_REDUCTION_FACTOR = 0.380f;

namespace window {
	bool create(GLFWwindow** lpWindow);
	bool setup(GLFWwindow* window);
	ImVec4 convert_color(const std::string& codeCouleurHTML);
	void tick(GLFWwindow* window);
	void cleanup(GLFWwindow* window);
}

namespace gui {
	void draw_tabs(void);
	void draw_menu(void);
}