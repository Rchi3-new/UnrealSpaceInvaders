// No Copyright today, comrade.


#include "MainMenuGameMode.h"

#include "Blueprint/UserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		UUserWidget* Menu = CreateWidget(GetWorld(), MainMenuWidgetClass);
		if (Menu)
		{
			Menu->AddToViewport();

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				PC->SetShowMouseCursor(true);
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}
}
