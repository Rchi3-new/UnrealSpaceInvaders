#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HostileProjectile.generated.h"

UCLASS()
class UNREALSPACEINVADERS_API AHostileProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHostileProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};