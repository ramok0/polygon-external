#include <ue4.hpp>

std::optional<TArray<class APlayerState*>> AGameState::get_player_array(void)
{
	if (this == nullptr) return std::nullopt;
	ONCE_GET_OFFSET("/Script/Engine.GameStateBase", "PlayerArray", PlayerArrayOffset);
	if (!PlayerArrayOffset) return std::nullopt;

	RPM(TArray<class APlayerState*>, (uintptr_t)this + PlayerArrayOffset, PlayerArray);
	if (!PlayerArraySuccess) return std::nullopt;

	return PlayerArray;
}