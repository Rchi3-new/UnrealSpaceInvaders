#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheWall.generated.h"

UCLASS()
class UNREALSPACEINVADERS_API ATheWall : public AActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	void ConstructWall();
	
	UFUNCTION()
	void WallOverlap(UPrimitiveComponent* OverlappedComponent,
	                AActor* OtherActor,
	                UPrimitiveComponent* OtherComp,
	                int32 OtherBodyIndex,
	                bool bFromSweep,
	                const FHitResult& SweepResult);
};
