#include <config.h>
#include <polygon.h>
#include <driver.h>
#include <window.h>
#include <cache.h>
#include <offsets.h>
#include <exploits.h>

int main(void) {
	if (!config::init()) {
		std::cerr << "failed to init configuration" << std::endl;
		return 1;
	}


	data::gameWindow = FindWindowA("UnrealWindow", "Polygon  ");
	if (!IsWindow((HWND)data::gameWindow)) {
		std::cerr << "Failed to get game window" << std::endl;
		return 1;
	}

	GetWindowThreadProcessId((HWND)data::gameWindow, &data::pid);

	if (!driver::init()) {
		std::cerr << "failed to initialize driver !" << std::endl;
		return 1;
	}

	data::base_address = driver::get_base_address();

	std::cout << "base address : " << std::hex << data::base_address << std::endl;

	cache_offsets();
	std::cout << "Successfully dumped " << std::dec << offset_cache.size() << " classes" << std::endl;

	std::thread(cache::cache_data).detach();

	GLFWwindow* window;
	if (!window::create(&window)) {
		std::cerr << "Failed to create window" << std::endl;
		return 1;
	}

	if (!window::setup(window)) {
		std::cerr << "Failed to setup window" << std::endl;
		window::cleanup(window);
		return 1;
	}

	while (!glfwWindowShouldClose(window)) {
		if (GetAsyncKeyState(VK_INSERT) & 0x01) {
			data::menu_open = !data::menu_open;
			glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, !data::menu_open);
		}

		window::tick(window);
	}

	window::cleanup(window);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	if (data::should_self_destruct)
	{
		exploits::panic();
	}

	return 0;
}