#include <ue4.hpp>

UGameInstance* UWorld::get_game_instance(void)
{
	SIMPLE_READ_PTR(UGameInstance*, "/Script/Engine.World", "OwningGameInstance", GameInstance);
}

AGameState* UWorld::get_game_state(void)
{
	SIMPLE_READ_PTR(AGameState*, "/Script/Engine.World", "GameState", GameState);
}

ULevel* UWorld::get_persistent_level(void)
{
	SIMPLE_READ_PTR(ULevel*, "/Script/Engine.World", "PersistentLevel", PersistentLevel);
}