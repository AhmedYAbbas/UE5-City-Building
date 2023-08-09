// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CBPlayerController.generated.h"

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class CITYBUILDING_API ACBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACBPlayerController();

	virtual void SetupInputComponent() override;
};
