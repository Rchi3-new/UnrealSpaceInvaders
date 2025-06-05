#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Hostile.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UNiagaraSystem;
class UWeaponComponent;
class AProjectile;

UCLASS()

class UNREALSPACEINVADERS_API AHostile : public AActor
{
        GENERATED_BODY()

public:
        AHostile();

       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
       float MoveSpeed = 1.0f;

       FORCEINLINE class UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> HostileCollision;

        UPROPERTY(EditDefaultsOnly)
        TObjectPtr<UStaticMeshComponent> HostileMesh;

        UPROPERTY(EditDefaultsOnly)
        TObjectPtr<UWeaponComponent> WeaponComponent;

	UPROPERTY()
	TObjectPtr<UNiagaraSystem> NiagaraEffect;

	UPROPERTY()
	TObjectPtr<USoundBase> BlastSound;

        UPROPERTY(EditDefaultsOnly)
        TSubclassOf<AProjectile> ActorProjectile;

	FTimerHandle ReloadTimerHandle;
	double MoveDirection = -1.0;
	int32 ProjectileCounter;
	const int32 ProjectileMax = 8;

	UFUNCTION()
	void ProjectileOverlap(UPrimitiveComponent* OverlappedComponent,
	                    AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex,
	                    bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void HostileDestroyFX();

	UFUNCTION()
	void DestroySound();

	UFUNCTION()
	void ChangeMovementDirection();

	UFUNCTION()
	void Move();

	UFUNCTION()
	void BeginFire();

	UFUNCTION()
	void SpawnProjectile();
	void ProjectileCheck();
};
