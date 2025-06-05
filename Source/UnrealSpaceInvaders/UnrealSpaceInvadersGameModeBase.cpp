#include "UnrealSpaceInvadersGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "AI/Hostile.h"

AUnrealSpaceInvadersGameModeBase::AUnrealSpaceInvadersGameModeBase()
{
       DifficultyMultiplier = 1.0f;
}

void AUnrealSpaceInvadersGameModeBase::IncreaseDifficulty()
{
       DifficultyMultiplier += 0.1f;

       TArray<AActor*> HostileActors;
       UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHostile::StaticClass(), HostileActors);

       for (AActor* Actor : HostileActors)
       {
               if (AHostile* Hostile = Cast<AHostile>(Actor))
               {
                       Hostile->MoveSpeed *= 1.1f;
                       if (UWeaponComponent* Weapon = Hostile->GetWeaponComponent())
                       {
                               Weapon->FireRate = FMath::Max(0.1f, Weapon->FireRate * 0.9f);
                       }
               }
       }
}

void AUnrealSpaceInvadersGameModeBase::NotifyHostileDestroyed(AHostile* DestroyedHostile)
{
       // Custom logic could be added here such as scoring or triggering new waves
}

