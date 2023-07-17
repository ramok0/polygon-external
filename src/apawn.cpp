#include <ue4.hpp>
#include <cache.hpp>

USkeletalMeshComponent* APawn::get_mesh(void)
{
	SIMPLE_READ_PTR(USkeletalMeshComponent*, "/Script/Engine.Character", "Mesh", Mesh);
}

UHealthStatsComponent* APawn::get_health_component(void)
{
	SIMPLE_READ_PTR(UHealthStatsComponent*, "/Script/POLYGON.PG_Game_Character", "HealthStatsComponent", HealthStatsComponent);
}

APlayerState* APawn::get_player_state(void)
{
	SIMPLE_READ_PTR(APlayerState*, "/Script/Engine.Pawn", "PlayerState", PlayerState);
}

bool APawn::move_at(FRotator look_at_coords)
{
	if (!this) return false;

	ONCE_GET_OFFSET("/Script/POLYGON.PG_Game_Character", "ControllerPitchRotation", ControllerPitchRotationOffset);
	if (!ControllerPitchRotationOffset) return false;

	struct rot_t {
		float Pitch;
		float Yaw;
	} rotation_stru;

	rotation_stru.Pitch = (float)look_at_coords.Pitch;
	rotation_stru.Yaw = (float)look_at_coords.Yaw;

	return driver::write<rot_t>((uintptr_t)this + ControllerPitchRotationOffset, rotation_stru);
}
