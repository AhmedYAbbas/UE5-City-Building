// Fill out your copyright notice in the Description page of Project Settings.


#include "CBCameraController.h"

#include "CBPlayerController.h"
#include "CBBuilding.h"
#include "CBGridManager.h"
#include "ClickableComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyInputConfigData.h"
#include "PloppableComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACBCameraController::ACBCameraController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ACBCameraController::BeginPlay()
{
	Super::BeginPlay();

	if (const auto CharacterMovementComponent = GetCharacterMovement())
	{
		InitialMovementSpeed = CharacterMovementComponent->MaxWalkSpeed;
		UpdateMovementSpeed();
	}

	SetPlacementMode(true);
}

// Called every frame
void ACBCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlacementMode)
	{
		UpdatePlacement();
	}
}

// Called to bind functionality to input
void ACBCameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);

			if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
			{
				PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &ACBCameraController::Move);
				PEI->BindAction(InputActions->InputStrafe, ETriggerEvent::Triggered, this, &ACBCameraController::Strafe);
				PEI->BindAction(InputActions->InputOrbit, ETriggerEvent::Triggered, this, &ACBCameraController::Orbit);
				PEI->BindAction(InputActions->InputZoom, ETriggerEvent::Triggered, this, &ACBCameraController::Zoom);
				PEI->BindAction(InputActions->InputPitch, ETriggerEvent::Triggered, this, &ACBCameraController::Pitch);
				PEI->BindAction(InputActions->InputFreeRoam, ETriggerEvent::Triggered, this, &ACBCameraController::FreeRoam);
				PEI->BindAction(InputActions->InputSetFreeRoam, ETriggerEvent::Started, this, &ACBCameraController::EnableFreeRoam);
				PEI->BindAction(InputActions->InputSetFreeRoam, ETriggerEvent::Completed, this, &ACBCameraController::DisableFreeRoam);

				// TODO: find a way to handle these inputs in the player controller
				PEI->BindAction(InputActions->InputPlaceBuilding, ETriggerEvent::Triggered, this, &ACBCameraController::SpawnBuilding);
			}
		}
	}
}

void ACBCameraController::Move(const FInputActionValue& Value)
{
	if (Controller)
	{
		const float MoveValue = Value.Get<float>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (MoveValue)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(Direction, MoveValue);
		}
	}
}

void ACBCameraController::Strafe(const FInputActionValue& Value)
{
	if (Controller)
	{
		const float StrafeValue = Value.Get<float>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (StrafeValue)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(Direction, StrafeValue);
		}
	}
}

void ACBCameraController::Orbit(const FInputActionValue& Value)
{
	if (Controller)
	{
		const float OrbitValue = Value.Get<float>();

		if (OrbitValue)
		{
			AddControllerYawInput(OrbitValue * OrbitSpeed);
		}
	}
}

void ACBCameraController::Zoom(const FInputActionValue& Value)
{
	if (Controller)
	{
		const float ZoomValue = Value.Get<float>();

		if (ZoomValue)
		{
			const float OldZoom = SpringArmComponent->TargetArmLength;
			const float NewZoom = ZoomValue * ZoomSpeed + OldZoom;
			SpringArmComponent->TargetArmLength = FMath::Clamp(NewZoom, MinZoom, MaxZoom);
			UpdateMovementSpeed();
		}
	}
}

void ACBCameraController::Pitch(const FInputActionValue& Value)
{
	if (Controller)
	{
		const float PitchValue = Value.Get<float>();

		if (PitchValue)
		{
			const float Pitch = PitchValue * PitchSpeed;
			FRotator Rotation = SpringArmComponent->GetComponentRotation();
			Rotation.Pitch += Pitch;
			Rotation.Pitch = FMath::ClampAngle(Rotation.Pitch, MinPitch, MaxPitch);
			SpringArmComponent->SetWorldRotation(Rotation);
		}
	}
}

void ACBCameraController::EnableFreeRoam(const FInputActionValue& Value)
{
	if (Controller)
	{
		bFreeRoam = true;
	}
}

void ACBCameraController::DisableFreeRoam(const FInputActionValue& Value)
{
	if (Controller)
	{
		bFreeRoam = false;
	}
}

void ACBCameraController::FreeRoam(const FInputActionValue& Value)
{
	if (Controller && bFreeRoam)
	{
		const FVector2D FreeRoamValue = Value.Get<FVector2D>();

		if (FreeRoamValue.X)
		{
			Orbit(FreeRoamValue.X);
		}

		if (FreeRoamValue.Y)
		{
			Pitch(FreeRoamValue.Y);
		}
	}
}

void ACBCameraController::UpdateMovementSpeed()
{
	const float SpeedModifier = SpringArmComponent->TargetArmLength / MinZoom;
	if (const auto CharacterMovementComponent = GetCharacterMovement())
	{
		CharacterMovementComponent->MaxWalkSpeed = InitialMovementSpeed * SpeedModifier;
	}
}

// TODO: find a way to implement this function in CBPlayerController
void ACBCameraController::SetPlacementMode(bool bEnable)
{
	if (bPlacementMode == bEnable)
	{
		return;
	}

	bPlacementMode = bEnable;
	if (bPlacementMode)
	{
		if (const UWorld* World = GetWorld())
		{
			Building = GetWorld()->SpawnActor(BuildingBlueprint);
			/*UPloppableComponent* PloppableComponent = Cast<UPloppableComponent>(AddComponentByClass(UPloppableComponent::StaticClass(), true, Building->GetTransform(), false));*/
		}

		auto ClickableComponent = Building->GetComponentByClass(UClickableComponent::StaticClass());
		if (ClickableComponent)
		{
			ClickableComponent->DestroyComponent();
		}
	}
	else if (!bPlacementMode && Building)
	{
		// TODO: find if there is a difference between this function and GetWorld()->DestroyActor()
		Building->Destroy();
	}
}

// TODO: find a way to implement this function in CBPlayerController
void ACBCameraController::UpdatePlacement()
{
	ACBPlayerController* PlayerController = Cast<ACBPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	FVector WorldLocation;
	FVector WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	if (const UWorld* World = GetWorld())
	{
		FHitResult HitResult;
		FVector Start = WorldLocation;
		FVector End = WorldLocation + (WorldDirection * 10000.0f);
		World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1);

		if (HitResult.bBlockingHit)
		{
			// TODO: this is an expensive operation
			// find a different way to reference the grid manager
			ACBGridManager* GridManager = Cast<ACBGridManager>(UGameplayStatics::GetActorOfClass(this, ACBGridManager::StaticClass()));
			FVector BuildingLocation = GridManager->GetClosestGridPosition(HitResult.Location);
			Building->SetActorLocation(BuildingLocation);
		}
	}
}

// TODO: find a way to implement this function in CBPlayerController
void ACBCameraController::SpawnBuilding()
{
	if (bPlacementMode)
	{
		const UPloppableComponent* PloppableComponent = Cast<UPloppableComponent>(Building->GetComponentByClass(UPloppableComponent::StaticClass()));
		if (PloppableComponent && PloppableComponent->bPlacementValid)
		{
			if (UWorld* World = GetWorld())
			{
				const FVector SpawnLocation = Building->GetActorLocation();
				AActor* ConstructedBuilding = World->SpawnActor(BuildingBlueprint, &SpawnLocation);

				const auto ConstructedPloppableComponent = ConstructedBuilding->GetComponentByClass(UPloppableComponent::StaticClass());
				if (ConstructedPloppableComponent)
				{
					ConstructedPloppableComponent->DestroyComponent();

					// To set the original material back after removing the ploppalbe component
					TArray<UActorComponent*> StaticMeshComponents;
					ConstructedBuilding->GetComponents(UStaticMeshComponent::StaticClass(), StaticMeshComponents);
					const auto BuildingActor = Cast<ACBBuilding>(ConstructedBuilding);
					for (const auto Component : StaticMeshComponents)
					{
						Cast<UStaticMeshComponent>(Component)->SetMaterial(0, BuildingActor->BaseMaterial);
					}
				}

				//SetPlacementMode(false);
			}
		}
	}
}
