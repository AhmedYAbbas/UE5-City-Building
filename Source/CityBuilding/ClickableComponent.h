// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClickableComponent.generated.h"

class UStaticMeshComponent;
class UMaterialInterface;

UCLASS(ClassGroup=(Custom), meta=(IsBlueprintBase, BlueprintSpawnableComponent))
class CITYBUILDING_API UClickableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClickableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void OnMouseClick(AActor* TouchedActor, FKey ButtonPressed);
	UFUNCTION()
	void OnMouseHover(AActor* TouchedActor);
	UFUNCTION()
	void OnMouseHoverEnd(AActor* TouchedActor);

private:
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* SelectedMaterial;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* UnselectedMaterial;

	bool bClicked = false;
};
