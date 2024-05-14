#include "HostileSwarm.h"

#include "Hostile.h"
#include "Kismet/GameplayStatics.h"

void AHostileSwarm::BeginPlay()
{
	Super::BeginPlay();
	SpawnHostiles();
	FTimerHandle CheckHostilesTimer;
	if (!CheckHostilesTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(CheckHostilesTimer, this, &AHostileSwarm::CheckHostiles, 2.0, true);
	}
}

void AHostileSwarm::SpawnHostiles() const
{
	const FVector SpawnLocation = GetActorLocation();
	int32 CountZ = 5;
	int32 CountY = 11;
	double Spacing = 120.0;
	for (int32 z = 1; z < CountZ; z++)
	{
		for (int32 y = 0; y < CountY; y++)
		{
			if (UWorld* World = GetWorld())
			{
				World->SpawnActor<AActor>(ActorToSpawn, (SpawnLocation + FVector(0.0, y * Spacing, z * Spacing)),
				                          FRotator::ZeroRotator);
			}
		}
	}
}

void AHostileSwarm::CheckHostiles()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHostile::StaticClass(), OutActors);
	TArray<AHostile*> EnemyArray;
	for (AActor* Actor : OutActors)
	{
		if (AHostile* Enemy = Cast<AHostile>(Actor))
		{
			EnemyArray.Add(Enemy);
		}
	}
	EnemyCount = EnemyArray.Num();

	if (EnemyCount <= 0)
	{
		UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()), false);
	}
}
