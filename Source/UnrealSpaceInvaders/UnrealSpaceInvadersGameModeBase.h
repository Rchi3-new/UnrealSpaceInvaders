#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealSpaceInvadersGameModeBase.generated.h"

UCLASS()
class UNREALSPACEINVADERS_API AUnrealSpaceInvadersGameModeBase : public AGameModeBase
{
       GENERATED_BODY()

public:
       AUnrealSpaceInvadersGameModeBase();

       UFUNCTION(BlueprintCallable, Category="Difficulty")
       void IncreaseDifficulty();

       void NotifyHostileDestroyed(class AHostile* DestroyedHostile);

       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Difficulty")
       float DifficultyMultiplier;
};
