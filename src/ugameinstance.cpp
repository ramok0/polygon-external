#include <ue4.hpp>


ULocalPlayer* UGameInstance::get_local_player(void)
{
	if (this == nullptr) return nullptr;
	ONCE_GET_OFFSET("/Script/Engine.GameInstance", "LocalPlayers", LocalPlayersOffset);
	if (!LocalPlayersOffset) return nullptr;

	RPM(TArray<ULocalPlayer*>, (uintptr_t)this + LocalPlayersOffset, LocalPlayerArray);
	if (!LocalPlayerArraySuccess) return nullptr;

	return LocalPlayerArray[0];
}