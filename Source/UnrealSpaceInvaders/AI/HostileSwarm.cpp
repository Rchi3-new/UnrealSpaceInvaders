#include "HostileSwarm.h"

#include "Hostile.h"
#include "Kismet/GameplayStatics.h"

namespace
{
	constexpr float HostileCheckIntervalSeconds = 2.0f;
	constexpr int32 HostileCountZ = 5;
	constexpr int32 HostileCountY = 11;
	constexpr double HostileSpacing = 120.0;
	constexpr int32 HostileStartZ = 1;
}

void AHostileSwarm::BeginPlay()
{
	Super::BeginPlay();
	SpawnHostiles();
	FTimerHandle CheckHostilesTimer;
	if (!CheckHostilesTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(CheckHostilesTimer, this, &AHostileSwarm::CheckHostiles, HostileCheckIntervalSeconds, true);
	}
}

void AHostileSwarm::SpawnHostiles() const
{
	const FVector SpawnLocation = GetActorLocation();
	int32 CountZ = HostileCountZ;
	int32 CountY = HostileCountY;
	double Spacing = HostileSpacing;
	for (int32 z = HostileStartZ; z < CountZ; z++)
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
