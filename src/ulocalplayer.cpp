#include <ue4.hpp>

APlayerController* ULocalPlayer::get_player_controller(void)
{
	SIMPLE_READ_PTR(APlayerController*, "/Script/Engine.Player", "PlayerController", PlayerController);
}