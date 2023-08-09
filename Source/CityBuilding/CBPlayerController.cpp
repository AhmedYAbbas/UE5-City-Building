// Fill out your copyright notice in the Description page of Project Settings.


#include "CBPlayerController.h"

ACBPlayerController::ACBPlayerController()
{
	SetShowMouseCursor(true);
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ACBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	
}

