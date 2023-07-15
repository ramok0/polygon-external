#include <polygon.hpp>
#include <ue4.hpp>
#include <overlay.hpp>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <chrono>
#include <ressources/roboto.h>

bool window::create(GLFWwindow** lpWindow)
{
	if (!glfwInit()) {
		return false;
	}

	if (!IsWindow(data::gameWindow)) return false;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (!monitor) {
		return false;
	}

	data::Width = glfwGetVideoMode(monitor)->width;
	data::Height = glfwGetVideoMode(monitor)->height;
	data::ScreenCenterX = (float)data::Width / 2.f;
	data::ScreenCenterY = (float)data::Height / 2.f;

	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(data::Width, data::Height, "discord", nullptr, nullptr);
	if (!window) return false;

	glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
	glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

	glfwSetWindowMonitor(window, NULL, 0, 0, data::Width, data::Height + 1, 0);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(config::config->data()->vsync ? 1 : 0);

	*lpWindow = window;
	return true;
}

bool window::setup(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_Text] = ImVec4(0.89f, 0.89f, 0.89f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.11f, 0.12f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.16f, 0.18f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.55f, 0.56f, 0.58f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.23f, 0.23f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.70f, 0.70f, 0.70f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.75f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.08f, 0.09f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);

	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(nostatic_compressed_data, nostatic_compressed_size, 16.f);
	ImGui::GetStyle().WindowTitleAlign.x = 0.5f;
	ImGui::GetStyle().WindowRounding = 12.f;
	ImGui::GetStyle().FrameRounding = 4.f;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	return true;
}

ImVec4 window::convert_color(const std::string& codeCouleurHTML)
{
	ImVec4 couleur;

	if (codeCouleurHTML.length() == 6)
	{
		std::string codeR = codeCouleurHTML.substr(0, 2);
		std::string codeG = codeCouleurHTML.substr(2, 2);
		std::string codeB = codeCouleurHTML.substr(4, 2);

		int r = std::stoi(codeR, nullptr, 16);
		int g = std::stoi(codeG, nullptr, 16);
		int b = std::stoi(codeB, nullptr, 16);

		couleur.x = static_cast<float>(r) / 255.0f;
		couleur.y = static_cast<float>(g) / 255.0f;
		couleur.z = static_cast<float>(b) / 255.0f;
		couleur.w = 1.0f; // Alpha à 1.0 par défaut
	}

	return couleur;
}

void window::tick(GLFWwindow* window)
{
	long long Timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	data::DeltaTime = (double)(Timestamp - data::LastFrameTimeStamp) / 100000;
	data::LastFrameTimeStamp = Timestamp;


	if (!IsWindow(data::gameWindow)) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return;
	}

	RECT rect;
	GetWindowRect(data::gameWindow, &rect);

	int Width = rect.right - rect.left;
	int Height = rect.bottom - rect.top;

	int oldPosX;
	int oldPosY;

	glfwGetWindowPos(window, &oldPosX, &oldPosY);

	if (data::Width != Width || data::Height != Height) {
		data::Width = Width;
		data::Height = Height;

		data::ScreenCenterX = (float)data::Width / 2;
		data::ScreenCenterY = (float)data::Height / 2;

		glfwSetWindowSize(window, data::Width, data::Height);
	}

	if (rect.left != oldPosX || rect.top != oldPosY) {
		glfwSetWindowPos(window, rect.left, rect.top);
	}



	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (data::menu_open) {
		gui::draw_menu();
	}

	overlay::draw();

	ImGui::Render();

	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
}

void window::cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}