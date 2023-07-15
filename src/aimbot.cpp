#include <ue4.hpp>
#include <cache.hpp>

//inline static long long LastFrameTimeStamp;
//inline static double DeltaTime;
//inline static void* pawn;



FRotator calc_angle(Vector3 src, Vector3 dst)
{
	auto delta = dst - src;
	double Distance = src.Distance(dst);

	float yaw = atan2f((float)delta.y, (float)delta.x) * DEG_TO_RAD3;
	float pitch = -((acosf(((float)delta.z / (float)Distance)) * DEG_TO_RAD3) - 90.f);

	FRotator angles = { pitch, yaw, 0 };

	return angles.clamp();
}

void modules::aimbot()
{
	if (!cache::closest_entity) return;
	if (!GetAsyncKeyState(VK_RBUTTON)) {
		return;
	}
	//long long Timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	//if ((*cache::closest_entity).Pawn != pawn) LastFrameTimeStamp = Timestamp;
	//DeltaTime = (double)(Timestamp - LastFrameTimeStamp);
	//LastFrameTimeStamp = Timestamp;

	Vector3 head_loc = (*cache::closest_entity).get_bone_with_rotation(config::config->data()->aim_bone);

	FRotator result = calc_angle(cache::view_info.Location, head_loc).clamp();

	if (config::config->data()->smoothing) {
		result = cache::view_info.Rotation.clamp().lerp(result, config::config->data()->smoothing_value);
	}

	cache::LocalPawn->move_at(result);
}