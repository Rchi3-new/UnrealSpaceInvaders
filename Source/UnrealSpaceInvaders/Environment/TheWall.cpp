#include "TheWall.h"
#include "UnrealSpaceInvaders/Projectile.h"

namespace
{
	constexpr int32 WallCount = 20;
	constexpr double WallSpacing = 10.0;
	constexpr double WallScale = 0.1;
}

void ATheWall::BeginPlay()
{
	Super::BeginPlay();
	ConstructWall();
}

void ATheWall::ConstructWall()
{

	int32 Count = WallCount;
	double Spacing = WallSpacing;
	int32 Row;
	int32 Column;

	for (Row = 0; Row < Count; Row++)
	{
		for (Column = 0; Column < Count; Column++)
		{
			if (UStaticMeshComponent* WallComponent = NewObject<UStaticMeshComponent>(
				this, UStaticMeshComponent::StaticClass()))
			{
				if (UStaticMesh* WallMesh = LoadObject<UStaticMesh>(
					nullptr, TEXT("StaticMesh'/Game/Hostiles/Mesh/SM_Cube.SM_Cube'")))
				{
					WallComponent->SetStaticMesh(WallMesh);
					WallComponent->SetupAttachment(RootComponent);
						WallComponent->SetRelativeTransform(
							FTransform(FRotator::ZeroRotator, FVector(0.0, Column * Spacing, Row * Spacing),
							           FVector(WallScale, WallScale, WallScale)));
					WallComponent->RegisterComponent();
					WallComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::WallOverlap);
				}
			}
		}
	}
}

void ATheWall::WallOverlap(UPrimitiveComponent* OverlappedComponent,
                           AActor* OtherActor,
                           UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex,
                           bool bFromSweep,
                           const FHitResult& SweepResult)
{
        if (Cast<AProjectile>(OtherActor))
        {
                if (OverlappedComponent)
                {
                        OverlappedComponent->DestroyComponent();
                }
        }
}
