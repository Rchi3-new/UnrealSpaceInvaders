#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HostileProjectile.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class UNREALSPACEINVADERS_API AHostileProjectile : public AActor
{
	GENERATED_BODY()

public:
	AHostileProjectile();

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> ProjectileCollisionCapsule;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent,
						   AActor* OtherActor,
						   UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex,
	                       bool bFromSweep,
	                       const FHitResult& SweepResult);
};