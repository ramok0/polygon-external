#include <wrappers.h>
#include <offsets.h>
#include <exploits.h>
#include <gamestructs.h>

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

bool AItem_Gun_General::set_air_down_time_multiplier(float value)
{
	if (!this) return false;
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "AimDownTimeMultiplier", AimDownTimeMultiplierOffset);

	driver::write((uintptr_t)this + AimDownTimeMultiplierOffset, value);

	return true;
}

bool AItem_Gun_General::set_recoil(float uprecoil, float backwardrecoil, float gunrecoilalphapershot, float gunrecoillift)
{
	if (!this) return false;
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunUpRecoil", GunUpRecoilOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunBackwardRecoil", GunBackwardRecoilOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunRecoilAlphaPerShot", GunRecoilAlphaPerShotOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunRecoilLift", GunRecoilLiftOffset);

	driver::write((uintptr_t)this + GunUpRecoilOffset, uprecoil);
	driver::write((uintptr_t)this + GunBackwardRecoilOffset, backwardrecoil);
	driver::write((uintptr_t)this + GunRecoilAlphaPerShotOffset, gunrecoilalphapershot);
	driver::write((uintptr_t)this + GunRecoilLiftOffset, gunrecoillift);

	return true;
}

bool AItem_Gun_General::set_spread(float current_spread, float spread_shot)
{
	if (!this) return false;

	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "CurrentSpread", CurrentSpreadOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "SpreadShot", SpreadShotOffset);

	driver::write((uintptr_t)this + CurrentSpreadOffset, current_spread);
	driver::write((uintptr_t)this + SpreadShotOffset, spread_shot);

	return true;
}

bool AItem_Gun_General::set_mobility(float mobility)
{
	if (!this) return false;

	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "Mobility", MobilityOffset);

	return driver::write((uintptr_t)this + MobilityOffset, mobility);
}

bool AItem_Gun_General::set_fire_rate(float rate)
{
	if (!this) return false;

	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "TimeBetweenShots", TimeBetweenShotsOffset);

	return driver::write((uintptr_t)this + TimeBetweenShotsOffset, rate);
}

bool AItem_Gun_General::set_reload_animations(void* ReloadCharacterAnimation, void* ReloadFullCharacterAnimation, void* ReloadGunAnimation, void* ReloadFullGunAnimation)
{
	if (!this) return false;

	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadCharacterAnimation", ReloadCharacterAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadFullCharacterAnimation", ReloadFullCharacterAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadGunAnimation", ReloadGunAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadFullGunAnimation", ReloadFullGunAnimationOffset);


	driver::write<void*>((uintptr_t)this + ReloadCharacterAnimationOffset, ReloadCharacterAnimation);
	driver::write<void*>((uintptr_t)this + ReloadFullCharacterAnimationOffset, ReloadFullCharacterAnimation);
	driver::write<void*>((uintptr_t)this + ReloadGunAnimationOffset, ReloadGunAnimation);
	return driver::write<void*>((uintptr_t)this + ReloadFullGunAnimationOffset, ReloadFullGunAnimation);
}

bool AItem_Gun_General::set_equip_animation(void* Animation)
{
	if (!this) return false;

	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "EquipAnimation", EquipAnimationOffset);

	return driver::write((uintptr_t)this + EquipAnimationOffset, Animation);
}

float AItem_Gun_General::get_air_down_time_multiplier(void)
{
	if (!this) return false;

	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "AimDownTimeMultiplier", AimDownTimeMultiplierOffset);

	return driver::unsafe_read<float>((uintptr_t)this + AimDownTimeMultiplierOffset);
}

RecoilStruct AItem_Gun_General::get_recoil(void)
{
	if (!this) return { 0 };
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunUpRecoil", GunUpRecoilOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunBackwardRecoil", GunBackwardRecoilOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunRecoilAlphaPerShot", GunRecoilAlphaPerShotOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunRecoilLift", GunRecoilLiftOffset);

	RecoilStruct data = { 0 };

	data.GunUpRecoil = driver::unsafe_read<float>((uintptr_t)this + GunUpRecoilOffset);
	data.GunBackwardRecoil = driver::unsafe_read<float>((uintptr_t)this + GunBackwardRecoilOffset);
	data.GunRecoilAlphaPerShot = driver::unsafe_read<float>((uintptr_t)this + GunRecoilAlphaPerShotOffset);
	data.GunRecoilLift = driver::unsafe_read<float>((uintptr_t)this + GunRecoilLiftOffset);

	return data;
}

SpreadData AItem_Gun_General::get_spread(void)
{
	if (!this) return { 0 };
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "CurrentSpread", CurrentSpreadOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "SpreadShot", SpreadShotOffset);

	SpreadData data = { 0 };

	data.CurrentSpread = driver::unsafe_read<float>((uintptr_t)this + CurrentSpreadOffset);
	data.SpreadShot = driver::unsafe_read<float>((uintptr_t)this + SpreadShotOffset);

	return data;
}

ReloadAnimations AItem_Gun_General::get_reload_animations(void)
{
	if (!this) return { nullptr };

	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadCharacterAnimation", ReloadCharacterAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadFullCharacterAnimation", ReloadFullCharacterAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadGunAnimation", ReloadGunAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadFullGunAnimation", ReloadFullGunAnimationOffset);

	ReloadAnimations animations;

	animations.ReloadCharacterAnimation = driver::unsafe_read<void*>((uintptr_t)this + ReloadCharacterAnimationOffset);
	animations.ReloadFullCharacterAnimation = driver::unsafe_read<void*>((uintptr_t)this + ReloadFullCharacterAnimationOffset);
	animations.ReloadGunAnimation = driver::unsafe_read<void*>((uintptr_t)this + ReloadGunAnimationOffset);
	animations.ReloadFullGunAnimation = driver::unsafe_read<void*>((uintptr_t)this + ReloadFullGunAnimationOffset);

	return animations;
}