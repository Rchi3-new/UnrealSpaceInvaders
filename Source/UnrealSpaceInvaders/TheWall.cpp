#include "TheWall.h"
#include "Projectile.h"
#include "HostileProjectile.h"

void ATheWall::BeginPlay()
{
	Super::BeginPlay();
	ConstructWall();
}

void ATheWall::ConstructWall()
{
	const int32 Count = 20;
	const double Spacing = 10.0;
	for (int32 j = 0; j < Count; j++)
	{
		for (int32 i = 0; i < Count; i++)
		{
			UStaticMeshComponent* WallComponent = NewObject<UStaticMeshComponent>(
				this, UStaticMeshComponent::StaticClass());
			if (WallComponent)
			{
				UStaticMesh* WallMesh = LoadObject<UStaticMesh>(
					nullptr, TEXT("StaticMesh'/Game/Hostiles/Mesh/SM_Cube.SM_Cube'"));
				if (WallMesh)
				{
					WallComponent->SetStaticMesh(WallMesh);
					WallComponent->SetupAttachment(RootComponent);
					WallComponent->SetRelativeTransform(
						FTransform(FRotator::ZeroRotator, FVector(0.0, i * Spacing, j * Spacing), FVector(0.1, 0.1, 0.1)));
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
	if(Cast<AHostileProjectile>(OtherActor) || Cast<AProjectile>(OtherActor))
	{
		if(OverlappedComponent)
		{
			OverlappedComponent->DestroyComponent();
		}
	}
}
