// No Copyright today, comrade.


#include "Projectile.h"
#include "Hostile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
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

// Called every frame
void AProjectile::Tick(float DeltaTime)

{
	Super::Tick(DeltaTime);
}

