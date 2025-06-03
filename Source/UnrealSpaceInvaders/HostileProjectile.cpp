#include "HostileProjectile.h"
#include "Components/BrushComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Environment/TheWall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Gameplay/PlayerShip.h"

AHostileProjectile::AHostileProjectile()
{
    ProjectileCollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProjectileCollision"));
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

    ensure(ProjectileCollisionCapsule);
    ensure(ProjectileMesh);
    ensure(ProjectileMovement);

    SetRootComponent(ProjectileCollisionCapsule);
    ProjectileMesh->SetupAttachment(ProjectileCollisionCapsule);

    ProjectileMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.6f));
    ProjectileCollisionCapsule->SetCapsuleHalfHeight(40.0f);
    ProjectileCollisionCapsule->SetCapsuleRadius(22.0f);
    
    ProjectileCollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHostileProjectile::OnOverlap);

    ProjectileMovement->InitialSpeed = 1000.0f;
    ProjectileMovement->MaxSpeed = 1000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void AHostileProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent,
                                    AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp,
                                    int32 OtherBodyIndex,
                                    bool bFromSweep,
                                    const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }
        if (OtherActor->IsA<APlayerShip>() || OtherComp->IsA<UBrushComponent>() || OtherActor->IsA<ATheWall>())
    {
        Destroy();
    }
}
