#include "imhelper.h"

ImColor get_color_from_float_array(float* color)
{
	if (color[0] > 1.f || 0 > color[0]) color[0] = 1.f;
	if (color[1] > 1.f || 0 > color[1]) color[1] = 1.f;
	if (color[2] > 1.f || 0 > color[2]) color[2] = 1.f;
	if (color[3] > 1.f || 0 > color[3]) color[3] = 1.f;

	return ImColor(color[0], color[1], color[2], color[3]);
}

void text_centered(std::string text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text.c_str());
}

bool center_tab_button(const char* label, ImVec2 button_size, float alignment)
{
	ImGui::Spacing();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4.f);
	return ImGui::Button(label, button_size);
}
