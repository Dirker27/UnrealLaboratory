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
		FVector NewGrabbedLocation = CalculateReachLineEnd();
		PhysicsHandle->SetTargetLocation(NewGrabbedLocation);
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
	PhysicsHandle->ReleaseComponent();
	UE_LOG(LogTemp, Warning, TEXT("[Grabber] Released Grab."));
}

void UGrabber::DrawReachLine()
{
	FVector ReachStart = CalculateReachLineStart();
	FVector ReachEnd = CalculateReachLineEnd();

	///- Debug Line -----------------------------------------=
	///
	DrawDebugLine(
		GetWorld(),
		ReachStart,
		ReachEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0,
		GripStrength / 10.f
	);
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult HitResult;

	FVector ReachStart = CalculateReachLineStart();
	FVector ReachEnd = CalculateReachLineEnd();

	///- Cast Ray ----------------------------------------=
	///
	bool hit = GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		ReachStart,
		ReachEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return HitResult;
}

FVector UGrabber::CalculateReachLineStart()
{
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLocation,
		OUT PlayerVPRotation
	);

	return PlayerVPLocation;
}

FVector UGrabber::CalculateReachLineEnd()
{
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLocation,
		OUT PlayerVPRotation
	);

	return PlayerVPLocation + (PlayerVPRotation.Vector() * ReachLength);
}