#include <ue4.hpp>
#include <cache.hpp>

FRotator calc_angle(Vector3 src, Vector3 dst)
{
	Vector3 vVector = dst - src;
	double pitch = atan2(vVector.z, sqrt((vVector.x * vVector.x) + (vVector.y * vVector.y) + (vVector.z * vVector.z))) * PI_180;
	double yaw = atan2(vVector.y, vVector.x) * PI_180;

	return FRotator(
		pitch,
		yaw,
		0);
}

void modules::aimbot()
{
	if (!cache::closest_entity) return;
	if (!GetAsyncKeyState(VK_RBUTTON)) {
		return;
	}

	Vector3 head_loc = (*cache::closest_entity).get_bone_with_rotation(config::config->data()->aim_bone);

	FRotator result = calc_angle(cache::view_info.Location, head_loc);

	if (config::config->data()->smoothing) {
		result = cache::view_info.Rotation.lerp(result, config::config->data()->smoothing_value);
	}

	cache::LocalPawn->move_at(result);
}