#include "Projectile.h"
#include "AI/Hostile.h"
#include "Components/BrushComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Gameplay/PlayerShip.h"
#include "Environment/TheWall.h"
#include "GameFramework/ProjectileMovementComponent.h"


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
        ProjectileMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.6));
        ProjectileCollisionCapsule->SetCapsuleHalfHeight(40.0);
        ProjectileCollisionCapsule->SetCapsuleRadius(22.0);
        ProjectileMovement->InitialSpeed = 1000.0f;
        ProjectileMovement->MaxSpeed = 1000.0f;
        ProjectileMovement->bRotationFollowsVelocity = true;
        ProjectileMovement->ProjectileGravityScale = 0.0f;
        ProjectileCollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ProjectileOverlap);
}

void AProjectile::ProjectileOverlap(UPrimitiveComponent* OverlappedComponent,
                                    AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp,
                                    int32 OtherBodyIndex,
                                    bool bFromSweep,
                                    const FHitResult& SweepResult)
{
        if (Owner == EProjectileOwner::Player)
        {
                if (Cast<AHostile>(OtherActor) || Cast<UBrushComponent>(OtherComp) || Cast<ATheWall>(OtherActor))
                {
                        Destroy();
                }
        }
        else if (Owner == EProjectileOwner::Hostile)
        {
                if (Cast<APlayerShip>(OtherActor) || Cast<UBrushComponent>(OtherComp) || Cast<ATheWall>(OtherActor))
                {
                        Destroy();
                }
        }
}
