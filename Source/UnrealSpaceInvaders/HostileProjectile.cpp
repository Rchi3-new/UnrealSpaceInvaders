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

    check(ProjectileCollisionCapsule);
    check(ProjectileMesh);
    check(ProjectileMovement);

    SetRootComponent(ProjectileCollisionCapsule);
    ProjectileMesh->SetupAttachment(ProjectileCollisionCapsule);

    ProjectileMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.6f));
    ProjectileCollisionCapsule->SetCapsuleHalfHeight(40.0f);
    ProjectileCollisionCapsule->SetCapsuleRadius(22.0f);
    
    ProjectileCollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::PlayerShipOverlap);
}

void AHostileProjectile::PlayerShipOverlap(UPrimitiveComponent* OverlappedComponent,
                                           AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp,
                                           int32 OtherBodyIndex,
                                           bool bFromSweep,
                                           const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor->IsA<APlayerShip>() || OtherComp->IsA<UBrushComponent>() || OtherActor->IsA<ATheWall>()))
    {
        Destroy();
    }
}
