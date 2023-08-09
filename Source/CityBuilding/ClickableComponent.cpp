 // Fill out your copyright notice in the Description page of Project Settings.


#include "ClickableComponent.h"

// Sets default values for this component's properties
UClickableComponent::UClickableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UClickableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Owner->OnClicked.AddDynamic(this, &UClickableComponent::OnMouseClick);
		Owner->OnBeginCursorOver.AddDynamic(this, &UClickableComponent::OnMouseHover);
		Owner->OnEndCursorOver.AddDynamic(this, &UClickableComponent::OnMouseHoverEnd);
	}
}


// Called every frame
void UClickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClickableComponent::OnMouseClick(AActor* TouchedActor, FKey ButtonPressed)
{
	bClicked = !bClicked;
	UStaticMeshComponent* StaticMeshRef = Cast<UStaticMeshComponent>(TouchedActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	// TODO: the logic should change when the materials are actually created and the game logic is defined
	if (StaticMeshRef)
	{
		if (!bClicked && StaticMeshRef->GetMaterial(0) != UnselectedMaterial)
		{
			StaticMeshRef->SetMaterial(0, UnselectedMaterial);
		}
		else if (bClicked && StaticMeshRef->GetMaterial(0) != SelectedMaterial)
		{
			StaticMeshRef->SetMaterial(0, SelectedMaterial);
		}
	}
}

void UClickableComponent::OnMouseHover(AActor* TouchedActor)
{
	UStaticMeshComponent* StaticMeshRef = Cast<UStaticMeshComponent>(TouchedActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	if (StaticMeshRef)
	{
		StaticMeshRef->SetRenderCustomDepth(true);
	}
}

void UClickableComponent::OnMouseHoverEnd(AActor* TouchedActor)
{
	UStaticMeshComponent* StaticMeshRef = Cast<UStaticMeshComponent>(TouchedActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	if (StaticMeshRef)
	{
		StaticMeshRef->SetRenderCustomDepth(false);
	}
}

