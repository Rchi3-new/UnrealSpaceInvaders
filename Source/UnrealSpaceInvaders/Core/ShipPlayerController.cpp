#include "ShipPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCameraActor.h"
#include "UnrealSpaceInvaders/ScoreWidget.h"
#include "UnrealSpaceInvaders/Gameplay/PlayerShip.h"
#include "UnrealSpaceInvaders/Components/ScoreComponent.h"

AShipPlayerController::AShipPlayerController()
{
	ScoreWidgetClass = UScoreWidget::StaticClass();
}

void AShipPlayerController::BeginPlay()
{
       Super::BeginPlay();
       SetInputMode(FInputModeGameOnly());

       AActor* CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCameraActor::StaticClass());
       CameraActor = Cast<APlayerCameraActor>(CameraActor);
       if (CameraActor)
       {
               SetViewTargetWithBlend(CameraActor);
       }

       if (ScoreWidgetClass)
       {
               ScoreWidget = CreateWidget<UScoreWidget>(this, ScoreWidgetClass);
               if (ScoreWidget)
               {
                       ScoreWidget->AddToViewport();
               }
       }

       if (APlayerShip* Ship = Cast<APlayerShip>(GetPawn()))
       {
               if (UScoreComponent* ScoreComponent = Ship->FindComponentByClass<UScoreComponent>())
               {
                       ScoreComponent->OnResourceValueChanged.AddDynamic(this, &AShipPlayerController::OnScoreChanged);
                       OnScoreChanged(ScoreComponent->GetScore());
               }
       }
}

void AShipPlayerController::OnScoreChanged(float NewScore)
{
       if (ScoreWidget)
       {
               ScoreWidget->UpdateScore(NewScore);
       }
}
