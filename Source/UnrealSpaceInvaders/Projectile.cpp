#include "Projectile.h"
#include "Hostile.h"
#include "Components/BrushComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
{
 	ProjectileCollisionCapsule=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	check(ProjectileCollisionCapsule);
	check(ProjectileMesh);
	check(ProjectileMovement);
	
	SetRootComponent(ProjectileCollisionCapsule);
	ProjectileMesh->SetupAttachment(ProjectileCollisionCapsule);
	ProjectileMesh->SetRelativeScale3D(FVector(0.4,0.4,0.6));
	ProjectileCollisionCapsule->SetCapsuleHalfHeight(40.0);
	ProjectileCollisionCapsule->SetCapsuleRadius(22.0);
	ProjectileCollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HostileOverlap);
}

void AProjectile::HostileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AHostile>(OtherActor) || Cast<UBrushComponent>(OtherComp))
	{
		Destroy();
	}
}