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

struct render_info_t {
	float LastSumbitTime;
	float LastRenderTime;
	float LastRenderTimeOnScreen;
};




UWorld* get_world(void);

