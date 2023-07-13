#include <ue4.hpp>

APawn* APlayerController::get_pawn(void)
{
	SIMPLE_READ_PTR(APawn*, "/Script/Engine.Controller", "Pawn", Pawn);
}

APlayerCameraManager* APlayerController::get_camera_manager(void)
{
	SIMPLE_READ_PTR(APlayerCameraManager*, "/Script/Engine.PlayerController", "PlayerCameraManager", PlayerCameraManager); //todo
}