// No Copyright today, comrade.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Hostile.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()

class UNREALSPACEINVADERS_API AHostile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHostile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UBoxComponent> HostileCollision;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> HostileMesh;

	UFUNCTION() void HostileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
