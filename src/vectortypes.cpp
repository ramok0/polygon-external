#include <vectortypes.h>
#include <cache.h>
#include <polygon.h>

Vector2Float world_to_screen(Vector3 world_location)
{
	Vector2Float screen_location;
	FMatrix rotation_matrix = FMatrix::from_rotator(cache::view_info.Rotation);

	Vector3 vDelta = world_location - cache::view_info.Location;

	Vector3 vAxisX = Vector3(rotation_matrix.M[0][0], rotation_matrix.M[0][1], rotation_matrix.M[0][2]);
	Vector3 vAxisY = Vector3(rotation_matrix.M[1][0], rotation_matrix.M[1][1], rotation_matrix.M[1][2]);
	Vector3 vAxisZ = Vector3(rotation_matrix.M[2][0], rotation_matrix.M[2][1], rotation_matrix.M[2][2]);

	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.0) {
		return { 0 };
	}

	screen_location.x = (float)(data::ScreenCenterX + vTransformed.x * (data::ScreenCenterX / tan(cache::view_info.FOV * DEG_TO_RAD2)) / vTransformed.z);
	screen_location.y = (float)(data::ScreenCenterY - vTransformed.y * (data::ScreenCenterX / tan(cache::view_info.FOV * DEG_TO_RAD2)) / vTransformed.z);

	return screen_location;
}
