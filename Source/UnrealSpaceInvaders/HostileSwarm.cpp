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
	constexpr int32 CountZ = 5;

	for (int32 j = 1; j < CountZ; j++)
	{
		constexpr int32 CountY = 15;
		for (int32 i = 0; i < CountY; i++)
		{
			if (UWorld* World = GetWorld())
			{
				constexpr double Spacing = 120.0;
				World->SpawnActor<AActor>(ActorToSpawn, (SpawnLocation + FVector(0.0, i * Spacing, j * Spacing)),
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

	UE_LOG(LogTemp, Warning, TEXT("Actors %d"), EnemyCount);
	if (EnemyCount<=0)
	{
		UGameplayStatics::OpenLevel(
			this, FName(GetWorld()->GetName()), false);
	}
}
