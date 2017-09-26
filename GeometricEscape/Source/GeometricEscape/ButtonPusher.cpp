// Copyright ToasterCat Productions, LLC.

#include "ButtonPusher.h"

#include "DrawDebugHelpers.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#include "ButtonAction.h"

#define OUT

// Sets default values for this component's properties
UButtonPusher::UButtonPusher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UButtonPusher::BeginPlay()
{
	Super::BeginPlay();
	this->BindInput();
}


// Called every frame
void UButtonPusher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LookingAtActor = GetFirstInteractableInReach().GetActor();
	if (LookingAtActor)
	{
		// UE_LOG(LogTemp, Warning, TEXT("[ButtonPusher] Looking at Actor {%s}"), *LookingAtActor->GetName());
		DrawReachLine();
	}
}


void UButtonPusher::BindInput()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		///- Action Bindings -----------------------------------=
		///
		Input->BindAction("INTERACT", IE_Pressed, this, &UButtonPusher::Push);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[ButtonPusher] Missing required component: InputComponent."));
	}
}

void UButtonPusher::Push()
{
	UE_LOG(LogTemp, Warning, TEXT("[ButtonPusher] < Click >"));

	AActor* Interactable = LookingAtActor;
	if (Interactable)
	{
		UButtonAction* action = Interactable->FindComponentByClass<UButtonAction>();
		if (action)
		{
			UE_LOG(LogTemp, Warning, TEXT("[ButtonPusher] Activating Interactable Actor {%s}"), *LookingAtActor->GetName());
			action->Press();
		}
	}
}


void UButtonPusher::DrawReachLine()
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
		10.f
	);
}

const FHitResult UButtonPusher::GetFirstInteractableInReach()
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
		FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return HitResult;
}

FVector UButtonPusher::CalculateReachLineStart()
{
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLocation,
		OUT PlayerVPRotation
	);

	return PlayerVPLocation;
}

FVector UButtonPusher::CalculateReachLineEnd()
{
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPLocation,
		OUT PlayerVPRotation
	);

	return PlayerVPLocation + (PlayerVPRotation.Vector() * ReachLength);
}