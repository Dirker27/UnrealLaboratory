// Copyright ToasterCat Productions, LLC.

#include "WallController.h"

#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"

#include "ActionReceiver.h"

// Sets default values for this component's properties
UWallController::UWallController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWallController::BeginPlay()
{
	Super::BeginPlay();

	ActionReciever = GetOwner()->FindComponentByClass<UActionReceiver>();
	if (!ActionReciever)
	{
		UE_LOG(LogTemp, Error, TEXT("[WallController] Missing required component: ActionReciever."));
	}
}


// Called every frame
void UWallController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActionReciever->IsActive())
	{
		TriggerRetract();
	}
}

void UWallController::TriggerRetract()
{
	OnRetract.Broadcast();
}

void UWallController::TriggerErect()
{
	OnErect.Broadcast();
}