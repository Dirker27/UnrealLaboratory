// Copyright ToasterCat Productions LLC - Please don't steal our shit.

#include "Grabber.h"

#include "Engine/World.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLocation,
		OUT PlayerVPRotation
	);

	UE_LOG(LogTemp, Warning, TEXT("[Grabber] Player Looking At: Loc[%s] Rot[%s]"),
		*PlayerVPLocation.ToCompactString(), *PlayerVPRotation.ToCompactString()
	);
}

