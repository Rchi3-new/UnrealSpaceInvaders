#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UnrealSpaceInvaders/Projectile.h"
#include "UnrealSpaceInvaders/Gameplay/PlayerShip.h"

namespace
{
	constexpr float DefaultFireRate = 1.0f;
	constexpr float DefaultProjectileSpeed = 500.0f;
	constexpr float DefaultProjectileMaxSpeed = 500.0f;
	constexpr float DefaultProjectileGravityScale = 0.0f;
	constexpr float DefaultSpawnOffsetZ = 50.0f;
}

UWeaponComponent::UWeaponComponent()
{
    FireRate = DefaultFireRate; // One shot per second
    ProjectileSpeed = DefaultProjectileSpeed; // Projectile speed
    ProjectileMaxSpeed = DefaultProjectileMaxSpeed;
    bRotationFollowsVelocity = true;
    ProjectileGravityScale = DefaultProjectileGravityScale;
    SpawnOffset = FVector(0.0f, 0.0f, DefaultSpawnOffsetZ); // Offset from the actor's center
    bFireUpwards = true; // Firing upwards by default
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::StartFiring()
{
	if (!FiringTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(FiringTimerHandle, this, &UWeaponComponent::Fire, FireRate, true);
	}
}

void UWeaponComponent::StopFiring()
{
        GetWorld()->GetTimerManager().ClearTimer(FiringTimerHandle);
}

void UWeaponComponent::FireOnce()
{
        Fire();
}

void UWeaponComponent::Fire()
{
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectileClass is not set for WeaponComponent!"));
		return;
	}

        if (AActor* Owner = GetOwner())
        {
                FVector Direction = bFireUpwards ? FVector::UpVector : FVector::DownVector;
                FVector SpawnLocation = Owner->GetActorLocation() + SpawnOffset;
                AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, Direction.Rotation());
                if (SpawnedProjectile)
                {
                        if (UProjectileMovementComponent* MoveComp = SpawnedProjectile->FindComponentByClass<UProjectileMovementComponent>())
                        {
                                MoveComp->Velocity = Direction * ProjectileSpeed;
                                MoveComp->InitialSpeed = ProjectileSpeed;
                                MoveComp->MaxSpeed = ProjectileMaxSpeed;
                                MoveComp->bRotationFollowsVelocity = bRotationFollowsVelocity;
                                MoveComp->ProjectileGravityScale = ProjectileGravityScale;
                        }
                        else if (UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(SpawnedProjectile->GetRootComponent()))
                        {
                                RootComponent->SetPhysicsLinearVelocity(Direction * ProjectileSpeed);
                        }

                       if (AProjectile* P = Cast<AProjectile>(SpawnedProjectile))
                       {
                               P->SetProjectileOwner(Cast<APlayerShip>(Owner) ? EProjectileOwner::Player : EProjectileOwner::Hostile);
                       }
                }

                OnFire.Broadcast();
        }
}
