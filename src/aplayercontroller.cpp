#include <wrappers.h>
#include <offsets.h>

APawn* APlayerController::get_pawn(void)
{
	SIMPLE_READ_PTR(APawn*, "/Script/Engine.Controller", "Pawn", Pawn);
}

APlayerCameraManager* APlayerController::get_camera_manager(void)
{
	SIMPLE_READ_PTR(APlayerCameraManager*, "/Script/Engine.PlayerController", "PlayerCameraManager", PlayerCameraManager); //todo
}

FRotator APlayerController::get_control_rotation(void)
{
	ONCE_GET_OFFSET("/Script/Engine.Controller", "ControlRotation", ControlRotationOffset);
	if (!ControlRotationOffset) return { 0 };
	
	RPM(FRotator, (uintptr_t)this + ControlRotationOffset, ControlRotation);
	if (!ControlRotationSuccess) return { 0 };
	
	return ControlRotation;
}

