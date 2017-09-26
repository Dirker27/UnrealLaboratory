// Copyright ToasterCat Productions, LLC.

#include "WallRetractor.h"

#include "GameFramework/Actor.h"

/*
 * ****************** DEPRECATION NOTICE **************************
 *                Use WallController Instead
 * ****************************************************************
 */

UWallRetractor::UWallRetractor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWallRetractor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	InitialLocation = Owner->GetActorLocation();
}


// Called every frame
void UWallRetractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWallRetractor::Retract()
{
	FVector* Offset = new FVector(0, 0, RetractHeight);
	FVector NewLocation = InitialLocation - *Offset;
	Owner->SetActorLocation(NewLocation);
}

void UWallRetractor::Erect()
{
	Owner->SetActorLocation(InitialLocation);
}

