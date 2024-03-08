// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ShipPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"


// Sets default values
APlayerShip::APlayerShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShipCollision=CreateDefaultSubobject<USphereComponent>(TEXT("ShipCollision"));
	ShipMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMovement=CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("ShipMovement"));

	check(ShipCollision);
	check(ShipMesh);
	check((ShipMovement));
		
	SetRootComponent(ShipCollision);

	ShipCollision->SetSphereRadius(50.0);
	ShipCollision->SetCollisionProfileName(TEXT("Pawn"));
	
	ShipMesh->SetupAttachment(ShipCollision);
}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	const APlayerController*PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ShipInputMappingContext,0);
		}
	}
}
void APlayerShip::Move(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();
	const FVector RightVector = GetActorRightVector();
	AddMovementInput(RightVector,FloatValue);
	
}

void APlayerShip::Attack(const FInputActionValue& Value)
{
	if(CanAttack)
	{
		CanAttack=false;
		SpawnActor();
		GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &APlayerShip::Reload, ReloadTime, false);
	}
}

void APlayerShip::Reload()
{
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
	CanAttack = true;
}

void APlayerShip::SpawnActor()
{
	const FVector SpawnLocation = GetActorLocation() + FVector(0,0,10);
	if (UWorld* World = GetWorld())
	{
		World->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator);
	}
}

// Called every frame
void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent*EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &APlayerShip::Move);
		EnhancedInputComponent->BindAction(AttackAction,ETriggerEvent::Triggered, this, &APlayerShip::Attack);
	}
}

