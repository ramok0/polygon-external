#include <ue4.hpp>

float AItem_Gun_General::get_time_between_shots(void)
{
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "TimeBetweenShots", TimeBetweenShotsOffset);
	if (!TimeBetweenShotsOffset) return 0.f;

	return driver::unsafe_read<float>((uintptr_t)this + TimeBetweenShotsOffset);
}

float AItem_Gun_General::get_mobility(void)
{
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "Mobility", MobilityOffset);
	if (!MobilityOffset) return 0.f;

	return driver::unsafe_read<float>((uintptr_t)this + MobilityOffset);
}

FText AItem_Gun_General::get_text(void)
{
	if (!this) return { 0 };

	ONCE_GET_OFFSET("/Script/POLYGON.Item_General", "ItemName", ItemNameOffset);
	if (!ItemNameOffset) return { 0 };

	FText text = driver::unsafe_read<FText>((uintptr_t)this + ItemNameOffset);
	if (!text) return { 0 };

	return text;
}
