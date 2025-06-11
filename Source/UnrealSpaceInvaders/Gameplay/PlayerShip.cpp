#include "PlayerShip.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealSpaceInvaders/Projectile.h"
#include "UnrealSpaceInvaders/Components/WeaponComponent.h"
#include "UnrealSpaceInvaders/Components/ScoreComponent.h"

APlayerShip::APlayerShip()
{
	ShipCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShipCollision"));
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
        ShipMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("ShipMovement"));
        WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
        ScoreComponent = CreateDefaultSubobject<UScoreComponent>(TEXT("ScoreComponent"));
        if (WeaponComponent)
        {
                WeaponComponent->SpawnOffset = FVector(0.0f, 0.0f, 100.0f);
                WeaponComponent->bFireUpwards = true;
        }

        check(ShipCollision);
        check(ShipMesh);
        check(ShipMovement);
        check(ScoreComponent);

	SetRootComponent(ShipCollision);
	ShipCollision->SetSphereRadius(50.0);
	ShipCollision->SetCollisionProfileName(TEXT("Pawn"));
	ShipCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerShip::PlayerShipOverlap);
	ShipMesh->SetupAttachment(ShipCollision);
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
        if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
        {
                if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
                        UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
                {
                        Subsystem->AddMappingContext(ShipInputMappingContext, 0);
                }
        }
        if (WeaponComponent)
        {
                WeaponComponent->ProjectileClass = ActorToSpawn;
        }
}

void APlayerShip::PlayerShipOverlap(UPrimitiveComponent* OverlappedComponent,
									AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp,
                                    int32 OtherBodyIndex,
                                    bool bFromSweep,
                                    const FHitResult& SweepResult)
{
        if (AProjectile* Projectile = Cast<AProjectile>(OtherActor))
        {
               if (Projectile->GetProjectileOwner() == EProjectileOwner::Hostile)
               {
                        ShipMesh->SetVisibility(false);
                        PlayerDeath();
                }
        }
}

void APlayerShip::Move(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();
	const FVector RightVector = GetActorRightVector();
	AddMovementInput(RightVector, FloatValue);
}

void APlayerShip::Attack(const FInputActionValue& Value)
{
        if (bCanAttack)
        {
                bCanAttack = false;
                if (WeaponComponent)
                {
                        WeaponComponent->FireOnce();
                }
                GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &APlayerShip::Reload, ReloadTime, false);
        }
}

void APlayerShip::PlayerDeath()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void APlayerShip::Reload()
{
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
        bCanAttack = true;
}


void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerShip::Move);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerShip::Attack);
	}
}