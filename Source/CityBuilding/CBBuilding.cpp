// Fill out your copyright notice in the Description page of Project Settings.


#include "CBBuilding.h"

// Sets default values
ACBBuilding::ACBBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACBBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

