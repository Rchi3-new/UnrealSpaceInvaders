#include "Hostile.h"

#include "HostileProjectile.h"
#include "NiagaraFunctionLibrary.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BrushComponent.h"

AHostile::AHostile()
{
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
	// ActorProjectile=LoadObject<>(nullptr, TEXT("Game/Hostiles/Projectile/BP_HostileProjectile"));
}

void AHostile::BeginPlay()
{
	Super::BeginPlay();
	BeginFire();
	
	if (FTimerHandle MoveTimer; !MoveTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(MoveTimer, this, &ThisClass::Move, 0.05, true);
	}
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
	else if (Cast<UBrushComponent>(OtherComp))
	{
		ChangeMovementDirection();
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

void AHostile::ChangeMovementDirection() const
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), OutActors);
	for (AActor* HostileActor :  OutActors)
	{
		if
		(AHostile* HostileActorDude = Cast<AHostile>(HostileActor))
			{
				HostileActorDude->MoveDirection *= -1.0;
			}
	}
}

void AHostile::Move()
{
	const FVector NewLocation = GetActorLocation() + FVector(0.0, MoveDirection, 0.0);
	SetActorLocation(NewLocation);
}

void AHostile::BeginFire()
{
	const float FireDelay = FMath::RandRange(2.0,5.0);
	if (!ReloadTimerHandle.IsValid())
	{
		GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AHostile::SpawnProjectile, FireDelay, false);
	}
}

void AHostile::SpawnProjectile()
{
	ProjectileCheck();
	if (ProjectileCounter < ProjectileMax)
	{
		const FVector SpawnLocation = GetActorLocation() + FVector(0.0,0.0,-100.0);

		if (UWorld* World = GetWorld())
		{
			World->SpawnActor<AActor>(ActorProjectile, SpawnLocation, FRotator(0,0,0));
			GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
			BeginFire();
		}
	}
}

void AHostile::ProjectileCheck()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHostile::StaticClass(), OutActors);

	TArray<AHostileProjectile*> ProjectilesArray;
	for (AActor* Actor: OutActors)
		if(AProjectile* Projectile = Cast<AProjectile>(Actor))
		{
			ProjectilesArray.Add(reinterpret_cast<TArray<AHostileProjectile*>::ElementType>(Projectile));
			ProjectileCounter = ProjectilesArray.Num();
		}
}

