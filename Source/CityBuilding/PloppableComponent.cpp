// Fill out your copyright notice in the Description page of Project Settings.

#include "PloppableComponent.h"

// Sets default values for this component's properties
UPloppableComponent::UPloppableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPloppableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Owner->OnActorBeginOverlap.AddDynamic(this, &UPloppableComponent::UpdateState);
		Owner->OnActorEndOverlap.AddDynamic(this, &UPloppableComponent::UpdateState);
	}
}


// Called every frame
void UPloppableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPloppableComponent::UpdateState(AActor* OverlappedActor, AActor* OtherActor)
{
	TArray<AActor*> OverlappingActors;
	OverlappedActor->GetOverlappingActors(OverlappingActors);
	if (OverlappingActors.IsEmpty())
	{
		bPlacementValid = true;
	}
	else
	{
		bPlacementValid = false;
	}

	TArray<UActorComponent*> StaticMeshComponents;
	OverlappedActor->GetComponents(UStaticMeshComponent::StaticClass(), StaticMeshComponents);
	for (const auto Component : StaticMeshComponents)
	{
		if (bPlacementValid)
		{
			Cast<UStaticMeshComponent>(Component)->SetMaterial(0, PloppableMaterial);
		}
		else
		{
			Cast<UStaticMeshComponent>(Component)->SetMaterial(0, InvalidPloppableMaterial);
		}
	}
}
