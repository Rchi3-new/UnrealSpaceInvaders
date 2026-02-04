#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityResource.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourceValueChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceDepleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceMaxedOut);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSPACEINVADERS_API UEntityResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntityResourceComponent();

protected:
	virtual void BeginPlay() override;

	static constexpr float DefaultInitialValue = 100.0f;
	static constexpr float DefaultMaxValue = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource", meta=(AllowPrivateAccess="true"))
	float InitialValue = DefaultInitialValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource", meta=(AllowPrivateAccess="true"))
	float MaxValue = DefaultMaxValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Resource", meta=(AllowPrivateAccess="true"))
	float CurrentValue;

	void SetCurrentValue(float NewValue);

public:
	UPROPERTY(BlueprintAssignable, Category="Resource")
	FOnResourceValueChanged OnResourceValueChanged;

	UPROPERTY(BlueprintAssignable, Category="Resource")
	FOnResourceDepleted OnResourceDepleted;

	UPROPERTY(BlueprintAssignable, Category="Resource")
	FOnResourceMaxedOut OnResourceMaxedOut;

	UFUNCTION(BlueprintCallable, Category="Resource")
	void IncreaseValue(float Amount);

	UFUNCTION(BlueprintCallable, Category="Resource")
	void DecreaseValue(float Amount);

	UFUNCTION(BlueprintCallable, Category="Resource")
	void IncreaseMaxValue(float Amount);

	UFUNCTION(BlueprintCallable, Category="Resource")
	void DecreaseMaxValue(float Amount);
	void ResetValue();
};
