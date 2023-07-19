#pragma once
typedef unsigned char uint8_t;

class UWorld;

struct HealthStatsComponentData {
	unsigned char Health;
	bool bIsAlive;
	bool bHealthProtection;
	float LastTimeTakeDamage;
	float Stamina;
};

struct RecoilStruct {
	float GunUpRecoil; // 0x3f4(0x04)
	float GunBackwardRecoil; // 0x3f8(0x04)
	float GunRecoilAlphaPerShot; // 0x3fc(0x04)
	float GunRecoilLift; // 0x400(0x04)
};

struct ReloadAnimations {
	void* ReloadCharacterAnimation;
	void* ReloadFullCharacterAnimation;
	void* ReloadGunAnimation;
	void* ReloadFullGunAnimation;
};

struct SpreadData {
	float SpreadShot;
	float CurrentSpread;
};

struct render_info_t {
	float LastSumbitTime;
	float LastRenderTime;
	float LastRenderTimeOnScreen;
};




UWorld* get_world(void);

