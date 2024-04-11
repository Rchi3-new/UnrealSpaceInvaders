// No Copyright today, comrade.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResouceEntity.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSPACEINVADERS_API UResouceEntity : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UResouceEntity();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
