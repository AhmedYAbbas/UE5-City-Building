// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PloppableComponent.generated.h"

class UMaterialInterface;

UCLASS(ClassGroup = (Custom), meta = (IsBlueprintBase, BlueprintSpawnableComponent))
class CITYBUILDING_API UPloppableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPloppableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool bPlacementValid = true;

private:
	UFUNCTION()
		void UpdateState(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Materials")
		UMaterialInterface* PloppableMaterial;
	UPROPERTY(EditDefaultsOnly, Category = "Materials")
		UMaterialInterface* InvalidPloppableMaterial;
};
