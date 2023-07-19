#include <game.h>
#include <polygon.h>
#include <driver.h>
#include <ue4.h>


UWorld* get_world(void)
{
	RPM(UWorld*, data::base_address + offsets::world, world);
	if (!worldSuccess) {
		return 0;
	}

	return world;
}

