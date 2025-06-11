#include "ScoreComponent.h"
#include <limits>

UScoreComponent::UScoreComponent()
{
		InitialValue = 0.0f;
		MaxValue = std::numeric_limits<float>::max();
		CurrentValue = InitialValue;
}

void UScoreComponent::AddScore(float Amount)
{
		IncreaseValue(Amount);
}

void UScoreComponent::ResetScore()
{
		ResetValue();
}
