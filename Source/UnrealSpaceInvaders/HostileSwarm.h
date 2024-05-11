#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HostileSwarm.generated.h"

UCLASS()
class UNREALSPACEINVADERS_API AHostileSwarm : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorToSpawn;

	int32 EnemyCount;
	void SpawnHostiles() const;
	void CheckHostiles();
};
