#include <wrappers.h>
#include <offsets.h>

APawn* APlayerState::get_pawn()
{
	SIMPLE_READ_PTR(APawn*, "/Script/Engine.PlayerState", "PawnPrivate", PawnPrivate);
}

uint8_t APlayerState::get_team_number(void)
{
	if (this == nullptr) return 0;
	ONCE_GET_OFFSET("/Script/POLYGON.PG_PlayerState_Game", "Team", TeamOffset);
	if (!TeamOffset) return 0;

	return driver::unsafe_read<uint8_t>((uintptr_t)this + TeamOffset);
}

std::string APlayerState::get_player_name(void)
{
	if (!this) return std::string();

	ONCE_GET_OFFSET("/Script/Engine.PlayerState", "PlayerNamePrivate", PlayerNamePrivateOffset);
	if (!PlayerNamePrivateOffset) return std::string();

	FString fStr = driver::unsafe_read<FString>((uintptr_t)this + PlayerNamePrivateOffset);

	return fStr.to_string();
}

UInventoryComponent_Game* APlayerState::get_inventory(void)
{
	SIMPLE_READ_PTR(UInventoryComponent_Game*, "/Script/POLYGON.PG_PlayerState_Game", "InventoryComponent", InventoryComponent);
}

bool APlayerState::is_a_bot()
{
	//char bShouldUpdateReplicatedPing : 1; // 0x29a(0x01)
	//char bIsSpectator : 1; // 0x29a(0x01)
	//char bOnlySpectator : 1; // 0x29a(0x01)
	//char bIsABot : 1; // 0x29a(0x01)
	//char pad_29A_4 : 1; // 0x29a(0x01)
	//char bIsInactive : 1; // 0x29a(0x01)
	//char bFromPreviousLevel : 1; // 0x29a(0x01)
	//char pad_29A_7 : 1; // 0x29a(0x01)

	ONCE_GET_OFFSET("/Script/Engine.PlayerState", "bShouldUpdateReplicatedPing", bShouldUpdateReplicatedPingOffset);

	if (!bShouldUpdateReplicatedPingOffset) return false;

	uint8_t data = driver::unsafe_read<uint8_t>((uintptr_t)this + bShouldUpdateReplicatedPingOffset);

	return (data >> 3) & 0x01;
}
