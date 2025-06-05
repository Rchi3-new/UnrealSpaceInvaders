#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UENUM()
enum class EProjectileOwner
{
    Player,
    Hostile
};

UCLASS()
class UNREALSPACEINVADERS_API AProjectile : public AActor
{
        GENERATED_BODY()

public:
        AProjectile();

       FORCEINLINE EProjectileOwner GetProjectileOwner() const { return ProjectileOwner; }

       FORCEINLINE void SetProjectileOwner(EProjectileOwner NewOwner) { ProjectileOwner = NewOwner; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> ProjectileCollisionCapsule;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

        UPROPERTY(EditDefaultsOnly)
        TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

        UPROPERTY(EditAnywhere)
        EProjectileOwner ProjectileOwner = EProjectileOwner::Player;

	UFUNCTION()
	void ProjectileOverlap(UPrimitiveComponent* OverlappedComponent,
	                    AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex,
	                    bool bFromSweep,
	                    const FHitResult& SweepResult);
};
