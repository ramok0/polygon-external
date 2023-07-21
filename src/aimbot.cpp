#include <modules.h>
#include <Windows.h>
#include <cache.h>
#include <config.h>
#include <wrappers.h>
#include <numbers>

FRotator calc_angle(Vector3 src, Vector3 dst)
{
	Vector3 vVector = dst - src;

	constexpr double RAD_TO_DEG = 180 / std::numbers::pi;

	FRotator angle;

	angle.Yaw = std::atan2(vVector.y, vVector.x) * RAD_TO_DEG;
	angle.Pitch = std::atan2(vVector.z, sqrt(vVector.x * vVector.x + vVector.y * vVector.y + vVector.z * vVector.z)) * RAD_TO_DEG;

	return angle;
}

void modules::aimbot()
{
	if (!cache::closest_entity || !GetAsyncKeyState(VK_RBUTTON)) return;

	Vector3 head_loc = (*cache::closest_entity).get_bone_with_rotation(config::config->data()->aim_bone);

	std::optional<FMinimalViewInfo> camera = cache::LocalController->get_camera_manager()->get_camera();
	if (!camera) return;

	FRotator result = calc_angle((*camera).Location, head_loc);

	if (config::config->data()->smoothing) {
		result = (*camera).Rotation.lerp(result, config::config->data()->smoothing_value);
	}

	cache::LocalPawn->move_at(result);
}