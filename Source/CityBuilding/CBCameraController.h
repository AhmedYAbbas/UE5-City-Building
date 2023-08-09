// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBCameraController.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UMyInputConfigData;
class ACBBuilding;

struct FInputActionValue;

UCLASS()
class CITYBUILDING_API ACBCameraController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACBCameraController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Strafe(const FInputActionValue& Value);
	void Orbit(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void Pitch(const FInputActionValue& Value);
	void FreeRoam(const FInputActionValue& Value);
	void EnableFreeRoam(const FInputActionValue& Value);
	void DisableFreeRoam(const FInputActionValue& Value);

	void UpdateMovementSpeed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void SetPlacementMode(bool bEnable);
	UFUNCTION()
	void UpdatePlacement();
	UFUNCTION()
	void SpawnBuilding();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UMyInputConfigData* InputActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float OrbitSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ZoomSpeed = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float PitchSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinZoom = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxZoom = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinPitch = 310.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxPitch = 350.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float InitialMovementSpeed;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY()
		AActor* Building;
	UPROPERTY(EditDefaultsOnly, Category = "Placement")
		TSubclassOf<ACBBuilding> BuildingBlueprint;

	bool bPlacementMode;
	bool bFreeRoam = false;
};
