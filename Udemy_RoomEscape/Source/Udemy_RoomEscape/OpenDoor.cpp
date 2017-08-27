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
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	WhitelistedActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	LastTimeDoorOpened = GetWorld()->GetTimeSeconds();

	Close();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(WhitelistedActor)) 
	{
		Open();
		LastTimeDoorOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		float deltaTime = GetWorld()->GetTimeSeconds() - LastTimeDoorOpened;
		if (deltaTime > DoorCloseDelay)
		{
			Close();
		}
	}
}

void UOpenDoor::Open() {
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::Close() {
	Owner->SetActorRotation(FRotator(0.0f, ClosedAngle, 0.0f));
}

