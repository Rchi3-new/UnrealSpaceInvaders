// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;
class UInputMappingContext;
struct FInputActionValue; 

UCLASS()
class UNREALSPACEINVADERS_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly) TObjectPtr<USphereComponent> ShipCollision;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ShipMesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UFloatingPawnMovement> ShipMovement;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UInputMappingContext> ShipInputMappingContext;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UInputAction> AttackAction;
	
	FTimerHandle ReloadTimerHandle;
	bool CanAttack = true;
	float ReloadTime = 0.5;
	
	void Move(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Reload();
	void SpawnActor();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
