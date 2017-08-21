// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"

#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString DisplayName = GetOwner()->GetName();
	FVector DisplayPos = GetOwner()->GetActorTransform().GetLocation();

	UE_LOG(LogTemp, Warning, TEXT("[PositionReport] %s standing by.\n|--- Initialized at %s"), *DisplayName, *DisplayPos.ToCompactString());
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

