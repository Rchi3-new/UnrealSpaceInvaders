#include "Projectile.h"
#include "Hostile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollisionCapsule=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	check(ProjectileCollisionCapsule);
	check(ProjectileMesh);
	check(ProjectileMovement);
	
	SetRootComponent(ProjectileCollisionCapsule);
	ProjectileMesh->SetupAttachment(ProjectileCollisionCapsule);
	ProjectileCollisionCapsule->SetCapsuleHalfHeight(40.0);
	ProjectileCollisionCapsule->SetCapsuleRadius(22.0);
	ProjectileMesh->SetRelativeScale3D(FVector(0.4,0.4,0.6));
    AActor::SetLifeSpan(3.0);
	ProjectileCollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HostileOverlap);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::HostileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AHostile>(OtherActor))
	{
		Destroy();
	}
}

void AProjectile::Tick(float DeltaTime)

{
	Super::Tick(DeltaTime);
}

