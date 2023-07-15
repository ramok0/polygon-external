#include <ue4.hpp>

AWorldSettings* ULevel::get_world_settings(void)
{
	SIMPLE_READ_PTR(AWorldSettings*, "/Script/Engine.Level", "WorldSettings", WorldSettings);
}