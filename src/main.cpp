#include <config.h>
#include <polygon.h>
#include <driver.h>
#include <window.h>
#include <cache.h>
#include <offsets.h>
#include <exploits.h>
#include <game.h>
#include <scanner.h>


int main(void) {
	if (!config::init()) {
		std::cerr << "failed to init configuration" << std::endl;
		return 1;
	}

	exploits::init();

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
	std::cout << "POLYGON-Win64-Shipping.exe : 0x" << std::uppercase << std::hex << data::base_address << std::endl;

	auto [image, image_length] = clone_image();
	if (!image) {
		std::cout << "Failed to read game image" << std::endl;
		return 1;
	}


	std::cout << "Searching for GObjects array.." << std::endl;
	offsets::objects = find_gobjects(image, image_length);
	std::cout << "Found GObjects array at 0x" << std::hex << std::uppercase << offsets::objects << std::endl;
	std::cout << "Searching for GWorld.." << std::endl;
	offsets::world = find_gworld(image, image_length);
	std::cout << "Found GWorld at 0x" << std::hex << std::uppercase << offsets::world << std::endl;
	std::cout << "Searching for FNamePool.." << std::endl;
	offsets::names = find_namepooldata(image, image_length);
	std::cout << "Found FNamePool at 0x" << std::hex << std::uppercase << offsets::names << std::endl;
	std::cout << "Searching for ComponentToWorld.." << std::endl;
	offsets::component_to_world = find_component_to_world(image, image_length);
	std::cout << "Found component_to_world : 0x" << std::hex << std::uppercase << offsets::component_to_world << std::endl;

	delete[] image;

	std::cout << "Loading internal classes... Please wait !" << std::endl;
	cache_offsets();
	std::cout << "Cached " << std::dec << offset_cache.size() << " internal reflected classes" << std::endl;

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

	std::cout << "Cleaning window.." << std::endl;
	window::cleanup(window);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	if (data::should_self_destruct)
	{
		std::cout << "Resetting exploits back to defaults.." << std::endl;
		exploits::panic();
	}

	std::cout << "Bye !" << std::endl;

	return 0;
}