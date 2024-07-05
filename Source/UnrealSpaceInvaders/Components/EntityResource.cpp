#include "EntityResource.h"


UEntityResource::UEntityResource()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UEntityResource::BeginPlay()
{
	
	Super::BeginPlay();
	
}

void UEntityResource::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

