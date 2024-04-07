#include "PlayerShip.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

APlayerShip::APlayerShip()
{
	ShipCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShipCollision"));
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("ShipMovement"));

	check(ShipCollision);
	check(ShipMesh);
	check(ShipMovement);
		
	SetRootComponent(ShipCollision);

	ShipCollision->SetSphereRadius(50.0);
	ShipCollision->SetCollisionProfileName(TEXT("Pawn"));
		
	ShipMesh->SetupAttachment(ShipCollision);
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	if(const APlayerController*PlayerController = Cast<APlayerController>(GetController()))
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

void APlayerShip::SpawnActor() const
{
	const FVector SpawnLocation = GetActorLocation() + FVector(0.0,0.0,100.0);
	if (UWorld* World = GetWorld())
	{
		World->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator);
	}
}

void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent*EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &APlayerShip::Move);
		EnhancedInputComponent->BindAction(AttackAction,ETriggerEvent::Triggered, this, &APlayerShip::Attack);
	}
}

