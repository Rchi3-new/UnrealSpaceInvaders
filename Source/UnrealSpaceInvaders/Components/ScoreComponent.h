#pragma once

#include "CoreMinimal.h"
#include "UnrealSpaceInvaders/Components/EntityResource.h"
#include "ScoreComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSPACEINVADERS_API UScoreComponent : public UEntityResourceComponent
{
		GENERATED_BODY()

public:
		UScoreComponent();

		UFUNCTION(BlueprintCallable, Category="Score")
		void AddScore(float Amount);

		UFUNCTION(BlueprintCallable, Category="Score")
		void ResetScore();
};
