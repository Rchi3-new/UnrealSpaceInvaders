// No Copyright today, comrade.

#include "NiagaraFunctionLibrary.h"
#include "Hostile.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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
	NiagaraEffect=LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Hostiles/VFX/NS_DestroyEffect"));
	BlastSound=LoadObject<USoundBase>(nullptr, TEXT("/Game/Hostiles/Sound/SW_DestroyHostile"));
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
		HostileDestroyFX();
		DestroySound();
		Destroy();
	}
}

void AHostile::HostileDestroyFX() const

{
	if(NiagaraEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraEffect, GetActorLocation());
	}
}

void AHostile::DestroySound() const
{
	if(BlastSound)
	{
		UGameplayStatics::PlaySound2D(this, BlastSound);
	}
}

// Called every frame
void AHostile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
