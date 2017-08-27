// Copyright ToasterCat Productions LLC - Please don't steal our shit.

#include "OpenDoor.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	WhitelistedActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(WhitelistedActor)) 
	{
		Open();
	}
}

void UOpenDoor::Open() {
	FRotator NewRotation = FRotator(0.0f, 50.0f, 0.0f);
	GetOwner()->SetActorRotation(NewRotation);
}

