#include <ue4.hpp>
#include <cache.hpp>

//inline static long long LastFrameTimeStamp;
//inline static double DeltaTime;
//inline static void* pawn;



FRotator calc_angle(Vector3 src, Vector3 dst)
{
	Vector3 delta = dst - src;
	float hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

	float yaw = atan2f((float)delta.y, (float)delta.x) * PI_180;
	float pitch = -((acosf(((float)delta.z / (float)hyp)) * PI_180) - 90.f);

	FRotator angles = { pitch, yaw, 0 };

	return angles.clamp();
}


void modules::aimbot()
{
	if (!cache::closest_entity) return;
	if (!GetAsyncKeyState(VK_RBUTTON)) {
		return;
	}

	//cache::LocalPawn->get_mesh()->get_bone_with_rotation(Bones::Head)

	Vector3 head_loc = (*cache::closest_entity).get_bone_with_rotation(config::config->data()->aim_bone);

	FRotator result = calc_angle(cache::view_info.Location, head_loc);

	if (config::config->data()->smoothing) {
		result = cache::view_info.Rotation.lerp(result, config::config->data()->smoothing_value);
	}

	cache::LocalPawn->move_at(result);
}