#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

UCLASS()
class UNREALSPACEINVADERS_API UScoreWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Score")
    void UpdateScore(float NewScore);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreText;
};
