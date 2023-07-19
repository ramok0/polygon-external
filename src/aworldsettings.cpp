#include <wrappers.h>
#include <offsets.h>

float AWorldSettings::get_world_to_meters(void)
{
	if (!this) return 0.0f;

	ONCE_GET_OFFSET("/Script/Engine.WorldSettings", "WorldToMeters", WorldToMetersOffset);
	if (!WorldToMetersOffset) return 0.0f;

	return driver::unsafe_read<float>((uintptr_t)this + WorldToMetersOffset);
}