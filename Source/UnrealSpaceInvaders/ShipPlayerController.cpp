// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPlayerController.h"
#include "Public/PlayerCameraActor.h"
#include "Kismet/GameplayStatics.h"

void AShipPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	AActor* CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCameraActor::StaticClass());
	CameraActor = Cast<class APlayerCameraActor>(CameraActor);
	if(CameraActor)
	{ 
		SetViewTargetWithBlend(CameraActor);
	}
}
