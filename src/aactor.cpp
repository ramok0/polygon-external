#include <ue4.hpp>

USceneComponent* AActor::get_root_component(void)
{
	SIMPLE_READ_PTR(USceneComponent*, "/Script/Engine.Actor", "RootComponent", RootComponent);
}