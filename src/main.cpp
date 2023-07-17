#include <polygon.hpp>
#include <objects.h>
#include <iostream>
#include <ue4.hpp>
#include <cache.hpp>

int main(void) {
	if (!config::init()) {
		std::cerr << "failed to init configuration" << std::endl;
		return 1;
	}

	data::gameWindow = FindWindowA("UnrealWindow", "Polygon  ");
	if (!IsWindow(data::gameWindow)) {
		std::cerr << "Failed to get game window" << std::endl;
		return 1;
	}

	GetWindowThreadProcessId(data::gameWindow, &data::pid);

	if (!driver::init()) {
		std::cerr << "failed to initialize driver !" << std::endl;
		return 1;
	}

	data::base_address = driver::get_base_address();

	std::cout << "base address : " << std::hex << data::base_address << std::endl;

	cache_offsets();
	std::cout << "Successfully dumped " << std::dec << offset_cache.size() << " classes" << std::endl;

	std::optional<FChunkedFixedUObjectArray> array = FChunkedFixedUObjectArray::get_array();
	if (!array) return 1;
	for (int i = 0; i < (*array).NumElements; i++) {
		UObjectBase* obj = (*array)[i];
		if (!obj) continue;

		std::cout << obj->getFullName() << std::endl;
	}

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

	return 0;
}