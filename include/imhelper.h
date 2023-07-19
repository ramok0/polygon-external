#pragma once
#include <window.h>

ImColor get_color_from_float_array(float* color);
void text_centered(std::string text);
bool center_tab_button(const char* label, ImVec2 button_size, float alignment = 0.5f);