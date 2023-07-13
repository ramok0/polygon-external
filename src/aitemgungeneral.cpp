#include <ue4.hpp>

float AItem_Gun_General::get_time_between_shots(void)
{
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "TimeBetweenShots", TimeBetweenShotsOffset);
	if (!TimeBetweenShotsOffset) return 0.f;

	return driver::unsafe_read<float>((uintptr_t)this + TimeBetweenShotsOffset);
}