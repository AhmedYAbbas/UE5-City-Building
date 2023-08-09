// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyInputConfigData.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class CITYBUILDING_API UMyInputConfigData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputStrafe;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputOrbit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputZoom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPitch;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputFreeRoam;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSetFreeRoam;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPlaceBuilding;
};
