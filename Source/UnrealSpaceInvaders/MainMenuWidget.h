#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class UNREALSPACEINVADERS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnPlayClicked();

	UFUNCTION()
	void OnSettingsClicked();

	UFUNCTION()
	void OnQuitClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
};
