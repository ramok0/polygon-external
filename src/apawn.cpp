#include <ue4.hpp>

USkeletalMeshComponent* APawn::get_mesh(void)
{
	SIMPLE_READ_PTR(USkeletalMeshComponent*, "/Script/Engine.Character", "Mesh", Mesh);
}

UHealthStatsComponent* APawn::get_health_component(void)
{
	SIMPLE_READ_PTR(UHealthStatsComponent*, "/Script/POLYGON.PG_Game_Character", "HealthStatsComponent", HealthStatsComponent);
}

APlayerState* APawn::get_player_state(void)
{
	SIMPLE_READ_PTR(APlayerState*, "/Script/Engine.Pawn", "PlayerState", PlayerState);
}
