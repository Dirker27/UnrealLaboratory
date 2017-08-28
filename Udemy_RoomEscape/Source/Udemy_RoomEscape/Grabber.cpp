// Copyright ToasterCat Productions LLC - Please don't steal our shit.

#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	///- Dependency Init + Validation -----------------------=
	///
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (! PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("[Grabber] Missing required component: PhysicsHandle."));
	}
	///
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		BindInput();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Grabber] Missing required component: InputComponent."));
	}
}

void UGrabber::BindInput() {
	Input->BindAction("GRAB", IE_Pressed, this, &UGrabber::Grab);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	///- Get player location + rotation ---------------------=
	///
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLocation,
		OUT PlayerVPRotation
	);

	///- Visual Debugging -----------------------------------=
	///
	///UE_LOG(LogTemp, Warning, TEXT("[Grabber] Player Looking At: Loc[%s] Rot[%s]"),
	///	*PlayerVPLocation.ToCompactString(), *PlayerVPRotation.ToCompactString()
	///);
	FVector PlayerReachEnd = PlayerVPLocation + (PlayerVPRotation.Vector() * ReachLength);
	DrawDebugLine(
		GetWorld(),
		PlayerVPLocation,
		PlayerReachEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0,
		GripStrength / 10.f
	);

	///- Cast Ray ----------------------------------------=
	///
	FHitResult HitResult;
	bool hit = GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerVPLocation,
		PlayerReachEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	if (hit)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Grabber] Currently Grabbing Actor[%s]"), *HitResult.GetActor()->GetName());
	}
}