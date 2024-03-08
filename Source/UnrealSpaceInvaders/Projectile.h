// No Copyright today, comrade.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class UNREALSPACEINVADERS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly) TObjectPtr<UCapsuleComponent> ProjectileCollisionCapsule;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UProjectileMovementComponent>ProjectileMovement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
