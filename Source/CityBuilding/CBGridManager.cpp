// Fill out your copyright notice in the Description page of Project Settings.

#include "CBGridManager.h"

#include "CBGridCell.h"
#include "Components/SphereComponent.h"

// Sets default values
ACBGridManager::ACBGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACBGridManager::BeginPlay()
{
	Super::BeginPlay();

	PopulateGrid();
}

// Called every frame
void ACBGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBGridManager::PopulateGrid()
{
	if (!GridArray.IsEmpty())
	{
		GridArray.Empty();
	}

	float WorldOffset = (0.5f * GridSize * CellSize) - (0.5f * CellSize);
	for (int i = 0; i < GridSize; i++)
	{
		for (int j = 0; j < GridSize; j++)
		{
			float X = (CellSize * j) - WorldOffset;
			float Y = (CellSize * i) - WorldOffset;
			FVector CellLocation(X, Y, 0);
			FTransform CellTransform(CellLocation);

			if (UWorld* World = GetWorld())
			{
				AActor* SpawnedGridCell = World->SpawnActor(GridCell, &CellLocation);
				GridArray.AddUnique(SpawnedGridCell);
			}
		}
	}
}

FVector ACBGridManager::GetClosestGridPosition(const FVector& InPosition)
{
	const FVector FirstGridCellLocation = GridArray[0]->GetActorLocation();
	FVector ClosestPosition = FirstGridCellLocation;
	float ClosestDistance = FVector::Distance(InPosition, ClosestPosition);

	for (const AActor* Cell : GridArray)
	{
		const FVector CellLocation = Cell->GetActorLocation();
		const float Distance = FVector::Distance(CellLocation, InPosition);
		if (Distance < ClosestDistance)
		{
			ClosestPosition = CellLocation;
			ClosestDistance = Distance;
		}
	}

	return ClosestPosition;
}

