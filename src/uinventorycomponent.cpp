#include <ue4.hpp>

AItem_Gun_General* UInventoryComponent_Game::get_current_weapon()
{
	SIMPLE_READ_PTR(AItem_Gun_General*, "/Script/POLYGON.InventoryComponent_Game", "CurrentGun", CurrentGun);
}