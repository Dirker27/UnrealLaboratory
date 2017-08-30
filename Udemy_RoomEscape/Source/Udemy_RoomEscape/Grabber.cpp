// Copyright ToasterCat Productions LLC - Please don't steal our shit.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/EngineTypes.h"
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
	this->ValidatePhysicsHandle();
	this->BindInput();
}

void UGrabber::ValidatePhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("[Grabber] Missing required component: PhysicsHandle."));
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///- If we've got something, move it -----------------=
	///
	if (PhysicsHandle->GrabbedComponent)
	{
		///- Calc target location ------------------------=
		///
		FVector PlayerVPLocation;
		FRotator PlayerVPRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerVPLocation,
			OUT PlayerVPRotation
		);
		FVector PlayerReachEnd = PlayerVPLocation + (PlayerVPRotation.Vector() * ReachLength);

		/// Apply
		PhysicsHandle->SetTargetLocation(PlayerReachEnd);
	}
}


void UGrabber::BindInput()
{
	///- Input Component ---------------------------------=
	///
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		///- Actual Bindings -----------------------------=
		///
		Input->BindAction("GRAB", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("GRAB", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Grabber] Missing required component: InputComponent."));
	}
}

void UGrabber::Grab()
{
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
	AActor* HitActor = Hit.GetActor();

	if (HitActor) // if HitActor != nullptr
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
		UE_LOG(LogTemp, Warning, TEXT("[Grabber] Currently Grabbing Actor[%s]."), *HitActor->GetName());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("[Grabber] Released Grab."));
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult HitResult;

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
	bool hit = GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerVPLocation,
		PlayerReachEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return HitResult;
}