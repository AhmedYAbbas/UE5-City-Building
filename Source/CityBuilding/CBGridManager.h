// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBGridManager.generated.h"

class ACBGridCell;

UCLASS()
class CITYBUILDING_API ACBGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetClosestGridPosition(const FVector& InPosition);

private:
	void PopulateGrid();

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> GridArray;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACBGridCell> GridCell;

	UPROPERTY(EditAnywhere)
	int GridSize = 10;
	UPROPERTY(EditAnywhere)
	int CellSize = 1000;
};
