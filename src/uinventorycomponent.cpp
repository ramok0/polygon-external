#include <wrappers.h>
#include <offsets.h>

AItem_Gun_General* UInventoryComponent_Game::get_current_weapon()
{
	SIMPLE_READ_PTR(AItem_Gun_General*, "/Script/POLYGON.InventoryComponent_Game", "CurrentGun", CurrentGun);
}

AItem_Gun_General* UInventoryComponent_Game::get_primary_weapon()
{
	SIMPLE_READ_PTR(AItem_Gun_General*, "/Script/POLYGON.InventoryComponent_Base", "PrimaryGun", PrimaryGun);
}

AItem_Gun_General* UInventoryComponent_Game::get_secondary_weapon()
{
	SIMPLE_READ_PTR(AItem_Gun_General*, "/Script/POLYGON.InventoryComponent_Base", "SecondaryGun", SecondaryGun);
}

bool UInventoryComponent_Game::set_grenades_count(char count)
{
	if(!this) return false;

	ONCE_GET_OFFSET("/Script/POLYGON.InventoryComponent_Game", "GrenadesNumber", GrenadesNumberOffset);

	return driver::write((uintptr_t)this + 0x100, count);
}
