// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBBuilding.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UMaterialInterface;

UCLASS()
class CITYBUILDING_API ACBBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* BaseMaterial;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* DefaultSceneRoot;
};
