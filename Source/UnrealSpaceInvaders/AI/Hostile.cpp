#include "Hostile.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BrushComponent.h"
#include "UnrealSpaceInvaders/Components/WeaponComponent.h"
#include "UnrealSpaceInvaders/Components/ScoreComponent.h"
#include "UnrealSpaceInvaders/Gameplay/PlayerShip.h"
#include "UnrealSpaceInvaders/Projectile.h"
#include "UnrealSpaceInvaders/UnrealSpaceInvadersGameModeBase.h"

namespace
{
	constexpr float WeaponSpawnOffsetZ = -100.0f;
	constexpr float HostileCollisionExtent = 51.0f;
	constexpr float HostileMoveInterval = 0.05f;
	constexpr double MovementDirectionFlip = -1.0;
	constexpr float DefaultDifficultyMultiplier = 1.0f;
	constexpr float FireDelayMinSeconds = 2.0f;
	constexpr float FireDelayMaxSeconds = 5.0f;
}

AHostile::AHostile()
{
	HostileCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HostileCollision"));
        HostileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HostileMesh"));
        WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
        if (WeaponComponent)
        {
                WeaponComponent->SpawnOffset = FVector(0.0f, 0.0f, WeaponSpawnOffsetZ);
                WeaponComponent->bFireUpwards = false;
        }

        check(HostileCollision);
        check(HostileMesh);
        check(WeaponComponent);

	SetRootComponent(HostileCollision);
	HostileMesh->SetupAttachment(HostileCollision);
	HostileCollision->SetBoxExtent(FVector(HostileCollisionExtent, HostileCollisionExtent, HostileCollisionExtent));
	HostileCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ProjectileOverlap);
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Hostiles/VFX/NS_DestroyEffect"));
	//	BlastSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Hostiles/Sound/SW_DestroyHostile"));
}

void AHostile::BeginPlay()
{
        Super::BeginPlay();
        if (WeaponComponent)
        {
                WeaponComponent->ProjectileClass = ActorProjectile;
        }
        BeginFire();

	if (FTimerHandle MoveTimer; !MoveTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(MoveTimer, this, &ThisClass::Move, HostileMoveInterval, true);
	}
}

void AHostile::ProjectileOverlap(UPrimitiveComponent* OverlappedComponent,
                                 AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex,
                                 bool bFromSweep,
                                 const FHitResult& SweepResult)
{
        if (Cast<AProjectile>(OtherActor))
        {

                Destroy();
        }
	else if (Cast<UBrushComponent>(OtherComp))
	{
		ChangeMovementDirection();
	}
}

void AHostile::HostileDestroyFX()

{
	if (NiagaraEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraEffect, GetActorLocation());
	}
}

void AHostile::DestroySound()
{
	if (BlastSound)
	{
		UGameplayStatics::PlaySound2D(this, BlastSound);
	}
}

void AHostile::ChangeMovementDirection()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), OutActors);
	for (AActor* HostileActor : OutActors)
	{
			if
			(AHostile* HostileActorDude = Cast<AHostile>(HostileActor))
			{
				HostileActorDude->MoveDirection *= MovementDirectionFlip;
			}
	}
}

void AHostile::Move()
{
       AUnrealSpaceInvadersGameModeBase* GM = GetWorld() ? GetWorld()->GetAuthGameMode<AUnrealSpaceInvadersGameModeBase>() : nullptr;
       const float Multiplier = GM ? GM->DifficultyMultiplier : DefaultDifficultyMultiplier;
       const FVector NewLocation = GetActorLocation() + FVector(0.0, MoveDirection * MoveSpeed * Multiplier, 0.0);
       SetActorLocation(NewLocation);
}

void AHostile::BeginFire()
{
	const float FireDelay = FMath::RandRange(FireDelayMinSeconds, FireDelayMaxSeconds);
	if (!ReloadTimerHandle.IsValid())
	{
		GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AHostile::SpawnProjectile, FireDelay, false);
	}
}

void AHostile::SpawnProjectile()
{
        ProjectileCheck();
        if (ProjectileCounter < ProjectileMax && WeaponComponent)
        {
                WeaponComponent->FireOnce();
                GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
                BeginFire();
        }
}

void AHostile::ProjectileCheck()
{
        TArray<AActor*> OutActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProjectile::StaticClass(), OutActors);

        TArray<AProjectile*> ProjectilesArray;
        for (AActor* Actor : OutActors)
        {
                if (AProjectile* Projectile = Cast<AProjectile>(Actor))
                {
                       if (Projectile->GetProjectileOwner() == EProjectileOwner::Hostile)
                       {
                                ProjectilesArray.Add(Projectile);
                        }
                }
        }
        ProjectileCounter = ProjectilesArray.Num();
}

void AHostile::Destroyed()
{
       Super::Destroyed();

       HostileDestroyFX();
       DestroySound();

       if (UWorld* World = GetWorld())
       {
               if (AUnrealSpaceInvadersGameModeBase* GM = World->GetAuthGameMode<AUnrealSpaceInvadersGameModeBase>())
               {
                       GM->NotifyHostileDestroyed(this);
               }
       }
}
