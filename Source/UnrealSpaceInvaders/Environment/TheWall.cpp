#include "TheWall.h"
#include "UnrealSpaceInvaders/HostileProjectile.h"
#include "UnrealSpaceInvaders/Projectile.h"

void ATheWall::BeginPlay()
{
	Super::BeginPlay();
	ConstructWall();
}

void ATheWall::ConstructWall()
{
	constexpr int32 Count = 20;
	for (int32 j = 0; j < Count; j++)
	{
		for (int32 i = 0; i < Count; i++)
		{
			if (UStaticMeshComponent* WallComponent = NewObject<UStaticMeshComponent>(
				this, UStaticMeshComponent::StaticClass()))
			{
				if (UStaticMesh* WallMesh = LoadObject<UStaticMesh>(
					nullptr, TEXT("StaticMesh'/Game/Hostiles/Mesh/SM_Cube.SM_Cube'")))
				{
					constexpr double Spacing = 10.0;
					WallComponent->SetStaticMesh(WallMesh);
					WallComponent->SetupAttachment(RootComponent);
					WallComponent->SetRelativeTransform(
						FTransform(FRotator::ZeroRotator, FVector(0.0, i * Spacing, j * Spacing),
						           FVector(0.1, 0.1, 0.1)));
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
	if (Cast<AHostileProjectile>(OtherActor) || Cast<AProjectile>(OtherActor))
	{
		if (OverlappedComponent)
		{
			OverlappedComponent->DestroyComponent();
		}
	}
}
