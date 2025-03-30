// No Copyright today, comrade.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class UNREALSPACEINVADERS_API AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	virtual void BeginPlay() override;
};
