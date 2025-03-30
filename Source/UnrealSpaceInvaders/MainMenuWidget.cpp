#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);

	if (SettingsButton)
		SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);

	if (QuitButton)
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
}

void UMainMenuWidget::OnPlayClicked()
{
	UGameplayStatics::OpenLevel(this, FName("MainLevel"));
}

void UMainMenuWidget::OnSettingsClicked()
{
	// Placeholder for settings logic
}

void UMainMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
