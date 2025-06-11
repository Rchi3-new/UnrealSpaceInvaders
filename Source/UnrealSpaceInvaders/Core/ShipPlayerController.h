#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShipPlayerController.generated.h"


UCLASS()
class UNREALSPACEINVADERS_API AShipPlayerController : public APlayerController
{
        GENERATED_BODY()

protected:
        virtual void BeginPlay() override;

        UPROPERTY(EditDefaultsOnly, Category="UI")
        TSubclassOf<class UScoreWidget> ScoreWidgetClass;

        UPROPERTY()
        UScoreWidget* ScoreWidget;

        UFUNCTION()
        void OnScoreChanged(float NewScore);
};
