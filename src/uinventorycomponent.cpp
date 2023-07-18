#include <ue4.hpp>

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
