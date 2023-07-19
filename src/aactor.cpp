#include <wrappers.h>
#include <offsets.h>

USceneComponent* AActor::get_root_component(void)
{
	SIMPLE_READ_PTR(USceneComponent*, "/Script/Engine.Actor", "RootComponent", RootComponent);
}