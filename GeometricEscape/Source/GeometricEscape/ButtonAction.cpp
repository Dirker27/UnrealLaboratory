// Copyright ToasterCat Productions, LLC.

#include "ButtonAction.h"


// Sets default values for this component's properties
UButtonAction::UButtonAction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UButtonAction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UButtonAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastButtonRelease += DeltaTime;
}

void UButtonAction::Press()
{
	UE_LOG(LogTemp, Warning, TEXT("[ButtonAction] < PRESS >"));

	OnButtonPress.Broadcast();
}

void UButtonAction::Release()
{
	OnButtonRelease.Broadcast();

}