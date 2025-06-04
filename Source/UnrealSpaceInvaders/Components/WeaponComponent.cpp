#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"

UWeaponComponent::UWeaponComponent()
{
    FireRate = 1.0f; // One shot per second
    ProjectileSpeed = 500.0f; // Projectile speed
    SpawnOffset = FVector(0.0f, 0.0f, 50.0f); // Offset from the actor's center
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
			UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(SpawnedProjectile->GetRootComponent());
			if (RootComponent)
			{
				RootComponent->SetPhysicsLinearVelocity(Direction * ProjectileSpeed);
			}
		}

		OnFire.Broadcast();
	}
}