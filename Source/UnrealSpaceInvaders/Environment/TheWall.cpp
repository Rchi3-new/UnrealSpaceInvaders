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
	int32 Count = 20;
	double Spacing = 10.0;
	for (int32 z = 0; z < Count; z++)
	{
		for (int32 y = 0; y < Count; y++)
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
						FTransform(FRotator::ZeroRotator, FVector(0.0, y * Spacing, z * Spacing),
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
