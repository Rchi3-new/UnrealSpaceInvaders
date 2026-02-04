#include "Projectile.h"
#include "AI/Hostile.h"
#include "Components/BrushComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Gameplay/PlayerShip.h"
#include "Environment/TheWall.h"
#include "GameFramework/ProjectileMovementComponent.h"

namespace
{
	constexpr float ProjectileScaleX = 0.4f;
	constexpr float ProjectileScaleY = 0.4f;
	constexpr float ProjectileScaleZ = 0.6f;
	constexpr float ProjectileCapsuleHalfHeight = 40.0f;
	constexpr float ProjectileCapsuleRadius = 22.0f;
	constexpr float ProjectileInitialSpeed = 1000.0f;
	constexpr float ProjectileMaxSpeed = 1000.0f;
	constexpr float ProjectileGravityScale = 0.0f;
}


AProjectile::AProjectile()
{
	ProjectileCollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProjectileCollision"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
        ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	check(ProjectileCollisionCapsule);
	check(ProjectileMesh);
	check(ProjectileMovement);

        SetRootComponent(ProjectileCollisionCapsule);
        ProjectileMesh->SetupAttachment(ProjectileCollisionCapsule);
        ProjectileMesh->SetRelativeScale3D(FVector(ProjectileScaleX, ProjectileScaleY, ProjectileScaleZ));
        ProjectileCollisionCapsule->SetCapsuleHalfHeight(ProjectileCapsuleHalfHeight);
        ProjectileCollisionCapsule->SetCapsuleRadius(ProjectileCapsuleRadius);
        ProjectileMovement->InitialSpeed = ProjectileInitialSpeed;
        ProjectileMovement->MaxSpeed = ProjectileMaxSpeed;
        ProjectileMovement->bRotationFollowsVelocity = true;
        ProjectileMovement->ProjectileGravityScale = ProjectileGravityScale;
        ProjectileCollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ProjectileOverlap);
}

void AProjectile::ProjectileOverlap(UPrimitiveComponent* OverlappedComponent,
                                    AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp,
                                    int32 OtherBodyIndex,
                                    bool bFromSweep,
                                    const FHitResult& SweepResult)
{
        if (ProjectileOwner == EProjectileOwner::Player)
        {
                if (Cast<AHostile>(OtherActor) || Cast<UBrushComponent>(OtherComp) || Cast<ATheWall>(OtherActor))
                {
                        Destroy();
                }
        }
        else if (ProjectileOwner == EProjectileOwner::Hostile)
        {
                if (Cast<APlayerShip>(OtherActor) || Cast<UBrushComponent>(OtherComp) || Cast<ATheWall>(OtherActor))
                {
                        Destroy();
                }
        }
}
