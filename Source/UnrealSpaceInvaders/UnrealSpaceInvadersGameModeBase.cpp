#include "UnrealSpaceInvadersGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "AI/Hostile.h"
#include "UnrealSpaceInvaders/Components/WeaponComponent.h"
#include "UnrealSpaceInvaders/Components/ScoreComponent.h"
#include "UnrealSpaceInvaders/Gameplay/PlayerShip.h"

namespace
{
	constexpr float DefaultDifficultyMultiplier = 1.0f;
	constexpr float DifficultyIncreaseStep = 0.1f;
	constexpr float HostileMoveSpeedMultiplier = 1.1f;
	constexpr float MinFireRate = 0.1f;
	constexpr float FireRateMultiplier = 0.9f;
	constexpr int32 DefaultPlayerIndex = 0;
	constexpr float HostileScoreValue = 10.0f;
}

AUnrealSpaceInvadersGameModeBase::AUnrealSpaceInvadersGameModeBase()
{
       DifficultyMultiplier = DefaultDifficultyMultiplier;
}


void AUnrealSpaceInvadersGameModeBase::IncreaseDifficulty()
{
	DifficultyMultiplier += DifficultyIncreaseStep;

        TArray<AActor*> HostileActors;
       UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHostile::StaticClass(), HostileActors);

       for (AActor* Actor : HostileActors)
       {
	               if (AHostile* Hostile = Cast<AHostile>(Actor))
	               {
	                       Hostile->MoveSpeed *= HostileMoveSpeedMultiplier;
	                       if (UWeaponComponent* Weapon = Hostile->GetWeaponComponent())
	                       {
	                               Weapon->FireRate = FMath::Max(MinFireRate, Weapon->FireRate * FireRateMultiplier);
	                       }
	               }
	       }
}

void AUnrealSpaceInvadersGameModeBase::NotifyHostileDestroyed(AHostile* DestroyedHostile) // Custom logic could be added here such as scoring or triggering new waves
{
               IncreaseDifficulty();

	               if (APlayerShip* Ship = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(this, DefaultPlayerIndex)))
	               {
	                       if (UScoreComponent* ScoreComp = Ship->FindComponentByClass<UScoreComponent>())
	                       {
	                               ScoreComp->AddScore(HostileScoreValue);
	                       }
	               }

}
