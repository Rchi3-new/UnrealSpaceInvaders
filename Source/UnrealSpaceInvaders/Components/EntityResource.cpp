#include "EntityResource.h"

UEntityResourceComponent::UEntityResourceComponent()
	: CurrentValue(InitialValue)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEntityResourceComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentValue = InitialValue;
}

void UEntityResourceComponent::SetCurrentValue(float NewValue)
{
	CurrentValue = FMath::Clamp(NewValue, 0.0f, MaxValue);
	OnResourceValueChanged.Broadcast(CurrentValue);

	if (CurrentValue == 0.0f)
	{
		OnResourceDepleted.Broadcast();
	}
	else if (CurrentValue == MaxValue)
	{
		OnResourceMaxedOut.Broadcast();
	}
}

void UEntityResourceComponent::IncreaseValue(float Amount)
{
	if (Amount > 0.0f)
	{
		SetCurrentValue(CurrentValue + Amount);
	}
}

void UEntityResourceComponent::DecreaseValue(float Amount)
{
	if (Amount > 0.0f)
	{
		SetCurrentValue(CurrentValue - Amount);
	}
}

void UEntityResourceComponent::IncreaseMaxValue(float Amount)
{
	if (Amount > 0.0f)
	{
		MaxValue += Amount;
		SetCurrentValue(CurrentValue);
	}
}

void UEntityResourceComponent::DecreaseMaxValue(float Amount)
{
	if (Amount > 0.0f && MaxValue - Amount >= 0.0f)
	{
		MaxValue -= Amount;
		SetCurrentValue(CurrentValue);
	}
}

void UEntityResourceComponent::ResetValue()
{
	SetCurrentValue(InitialValue);
}
