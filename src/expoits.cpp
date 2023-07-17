#include <ue4.hpp>
#include <cache.hpp>

void exploits::infinite_stamina(void)
{
	if (!config::config->data()->infinite_stamina) return;

	ONCE_GET_OFFSET("/Script/POLYGON.HealthStatsComponent", "Stamina", StaminaOffset);

	if (!StaminaOffset) return;
	if (!cache::LocalHealthStatsComponent) return;

	driver::write<float>((uintptr_t)cache::LocalHealthStatsComponent + StaminaOffset, 100.f);
}

inline std::unordered_map<void*, float> original_time_between_shots;
inline std::unordered_map<void*, float> original_mobility;
inline std::unordered_map<void*, std::unordered_map<uint64_t, void*>> original_reload_animations;

void exploits::rapid_fire()
{
	if (!config::config->data()->rapid_fire) return;
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "TimeBetweenShots", TimeBetweenShotsOffset);
	if (!TimeBetweenShotsOffset) return;
	if (!cache::LocalCurrentWeapon) return;
	if (!original_time_between_shots.contains(cache::LocalCurrentWeapon)) {
		original_time_between_shots[cache::LocalCurrentWeapon] = cache::LocalCurrentWeapon->get_time_between_shots();
	}
	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + TimeBetweenShotsOffset, config::config->data()->time_between_shots);
}

void exploits::no_spread(void)
{
	if (!config::config->data()->no_spread) return;
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "CurrentSpread", CurrentSpreadOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "SpreadShot", SpreadShotOffset);
	if (!SpreadShotOffset || !CurrentSpreadOffset || !cache::LocalCurrentWeapon) return;

	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + CurrentSpreadOffset, 0.f);
	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + SpreadShotOffset, 0.f);
}

void exploits::no_recoil(void)
{
	if (!config::config->data()->no_recoil) return;

	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunUpRecoil", GunUpRecoilOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunBackwardRecoil", GunBackwardRecoilOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunRecoilAlphaPerShot", GunRecoilAlphaPerShotOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "GunRecoilLift", GunRecoilLiftOffset);

	if (!GunUpRecoilOffset || !GunBackwardRecoilOffset || !GunRecoilAlphaPerShotOffset ||!GunRecoilLiftOffset || !cache::LocalCurrentWeapon) return;

	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + GunUpRecoilOffset, 0.f);
	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + GunBackwardRecoilOffset, 0.f);
	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + GunRecoilAlphaPerShotOffset, 0.f);
	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + GunRecoilLiftOffset, 0.f);
}

void exploits::instantaim()
{
	if (!config::config->data()->instant_aim) return;
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "AimDownTimeMultiplier", AimDownTimeMultiplierOffset);
	if (!AimDownTimeMultiplierOffset) return;
	if (!cache::LocalCurrentWeapon) return;

	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + AimDownTimeMultiplierOffset, 1000.f);
}

void exploits::fast_move()
{
	if (!config::config->data()->fast_move) return;
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "Mobility", MobilityOffset);
	if (!MobilityOffset || !cache::LocalCurrentWeapon) return;

	if (!original_mobility.contains(cache::LocalCurrentWeapon)) {
		original_mobility[cache::LocalCurrentWeapon] = cache::LocalCurrentWeapon->get_mobility();
	}

	driver::write<float>((uintptr_t)cache::LocalCurrentWeapon + MobilityOffset, original_mobility[cache::LocalCurrentWeapon] * 2.f);
}

void exploits::instant_reload(void)
{
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadCharacterAnimation", ReloadCharacterAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadFullCharacterAnimation", ReloadFullCharacterAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadGunAnimation", ReloadGunAnimationOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.Item_Gun_General", "ReloadFullGunAnimation", ReloadFullGunAnimationOffset);

	if (!ReloadCharacterAnimationOffset || !ReloadFullCharacterAnimationOffset || !ReloadGunAnimationOffset || !ReloadFullGunAnimationOffset) return;

	if (!config::config->data()->instant_reload) {
		if (original_reload_animations.contains(cache::LocalCurrentWeapon)) {
			driver::write<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadCharacterAnimationOffset, original_reload_animations[cache::LocalCurrentWeapon][ReloadCharacterAnimationOffset]);
			driver::write<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadFullCharacterAnimationOffset, original_reload_animations[cache::LocalCurrentWeapon][ReloadFullCharacterAnimationOffset]);
			driver::write<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadGunAnimationOffset, original_reload_animations[cache::LocalCurrentWeapon][ReloadGunAnimationOffset]);
			driver::write<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadFullGunAnimationOffset, original_reload_animations[cache::LocalCurrentWeapon][ReloadFullGunAnimationOffset]);
			original_reload_animations.erase(cache::LocalCurrentWeapon);
		}

		return;
	}

	if (!original_reload_animations.contains(cache::LocalCurrentWeapon))
	{
		std::unordered_map<uint64_t, void*> map;
		map.insert(std::make_pair(ReloadCharacterAnimationOffset, driver::unsafe_read<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadCharacterAnimationOffset)));
		map.insert(std::make_pair(ReloadFullCharacterAnimationOffset, driver::unsafe_read<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadFullCharacterAnimationOffset)));
		map.insert(std::make_pair(ReloadGunAnimationOffset, driver::unsafe_read<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadGunAnimationOffset)));
		map.insert(std::make_pair(ReloadFullGunAnimationOffset, driver::unsafe_read<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadFullGunAnimationOffset)));

		original_reload_animations.insert(std::make_pair(cache::LocalCurrentWeapon, map));
	}

	driver::write<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadCharacterAnimationOffset, nullptr);
	driver::write<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadFullCharacterAnimationOffset, nullptr);
	driver::write<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadGunAnimationOffset, nullptr);
	driver::write<void*>((uintptr_t)cache::LocalCurrentWeapon + ReloadFullGunAnimationOffset, nullptr);
}

float exploits::get_original_mobility(void)
{
	return original_mobility.contains(cache::LocalCurrentWeapon) ? original_mobility[cache::LocalCurrentWeapon] : 0;
}

float exploits::get_original_time_between_shots(void)
{
	return original_time_between_shots.contains(cache::LocalCurrentWeapon) ? original_time_between_shots[cache::LocalCurrentWeapon] : 0;
}
