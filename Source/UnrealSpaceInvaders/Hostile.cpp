// No Copyright today, comrade.


#include "Hostile.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"

// Sets default values
AHostile::AHostile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HostileCollision=CreateDefaultSubobject<UBoxComponent>(TEXT("HostileCollision"));
	HostileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HostileMesh"));


	check(HostileCollision);
	check(HostileMesh);


	SetRootComponent(HostileCollision);
	HostileMesh->SetupAttachment(HostileCollision);
	HostileCollision->SetBoxExtent(FVector(51.0,51.0,51.0));
	HostileCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HostileOverlap);
}

// Called when the game starts or when spawned
void AHostile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHostile::HostileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AProjectile>(OtherActor))
	{
		Destroy();
	}
}

// Called every frame
void AHostile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

