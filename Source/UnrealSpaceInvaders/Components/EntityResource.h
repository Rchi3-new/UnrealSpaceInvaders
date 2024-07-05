#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityResource.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSPACEINVADERS_API UEntityResource : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntityResource();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
