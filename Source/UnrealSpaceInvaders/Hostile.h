#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Hostile.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()

class UNREALSPACEINVADERS_API AHostile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHostile();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> HostileCollision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> HostileMesh;

	UPROPERTY()
	TObjectPtr<UNiagaraSystem> NiagaraEffect;

	UPROPERTY()
	TObjectPtr<USoundBase> BlastSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorProjectile;

	FTimerHandle ReloadTimerHandle;
	double MoveDirection = -1.0;
	int32 ProjectileCounter;
	const int32 ProjectileMax = 8;
	
	UFUNCTION()
	void HostileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HostileDestroyFX() const;

	UFUNCTION()
	void DestroySound() const;

	UFUNCTION()
	void ChangeMovementDirection() const;

	UFUNCTION()
	void Move();

	UFUNCTION()
	void BeginFire();

	UFUNCTION()
	void SpawnProjectile();
	void ProjectileCheck();
};