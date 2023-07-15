#include "polygon.hpp"

ImColor get_color_from_float_array(float* color)
{
	if (color[0] > 1.f || 0 > color[0]) color[0] = 1.f;
	if (color[1] > 1.f || 0 > color[1]) color[1] = 1.f;
	if (color[2] > 1.f || 0 > color[2]) color[2] = 1.f;
	if (color[3] > 1.f || 0 > color[3]) color[3] = 1.f;

	return ImColor(color[0], color[1], color[2], color[3]);
}
