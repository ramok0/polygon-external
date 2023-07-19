#include <wrappers.h>
#include <offsets.h>

std::optional<HealthStatsComponentData> UHealthStatsComponent::get_data()
{
	if (this == nullptr) return std::nullopt;
	ONCE_GET_OFFSET("/Script/POLYGON.HealthStatsComponent", "Health", HealthOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.HealthStatsComponent", "bIsAlive", bIsAliveOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.HealthStatsComponent", "bHealthProtection", bHealthProtectionOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.HealthStatsComponent", "LastTimeTakeDamage", LastTimeTakeDamageOffset);
	ONCE_GET_OFFSET("/Script/POLYGON.HealthStatsComponent", "Stamina", StaminaOffset);

	if (!HealthOffset ||
		!bIsAliveOffset ||
		!bHealthProtectionOffset ||
		!LastTimeTakeDamageOffset ||
		!StaminaOffset)
	{
		return std::nullopt;
	}

	unsigned char* buffer = new unsigned char[0x100];
	if (!buffer) return std::nullopt;

	if (!driver::read((uintptr_t)this, (uintptr_t)buffer, 0x100)) {
		delete[] buffer;
		return std::nullopt;
	}

	HealthStatsComponentData result;

	result.Health = buffer[HealthOffset];
	result.bIsAlive = buffer[bIsAliveOffset] == 1;
	result.bHealthProtection = buffer[bHealthProtectionOffset] == 1;
	result.LastTimeTakeDamage = *(float*)&buffer[LastTimeTakeDamageOffset];
	result.Stamina = *(float*)&buffer[StaminaOffset];

	delete[] buffer;

	return result;
}