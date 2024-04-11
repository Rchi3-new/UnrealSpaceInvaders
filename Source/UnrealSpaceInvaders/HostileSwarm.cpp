#include "Hostile.h"
#include "HostileSwarm.h"

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
	double Spacing = 120.0;
	const int32 CountY = 20;
	const int32 CountZ = 5;

	for (int32 j = 1; j < CountZ; j++)
	{
		for (int32 i = 0; i < CountY; i++)
		{
			if (UWorld* World = GetWorld())
			{
				World->SpawnActor<AActor>(ActorToSpawn, (SpawnLocation + FVector(0.0, i + Spacing, 0.0)),
				                          FRotator::ZeroRotator);
			}
		}
	}
}

void AHostileSwarm::CheckHostiles()
{
}
