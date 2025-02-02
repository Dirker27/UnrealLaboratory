// Copyright ToasterCat Productions LLC - Please don't steal our shit.

#include "OpenDoor.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#define OUT

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

	Close();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("[OpenDoor] Missing required component: PressurePlate."));
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CalculateTotalMassOfActorsOnPlate() > TriggerMass)
	{
		Open();
	}
	else
	{
		Close();
	}
}

void UOpenDoor::Open()
{
	// Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));

	OnOpen.Broadcast();
}

void UOpenDoor::Close()
{
	//Owner->SetActorRotation(FRotator(0.0f, ClosedAngle, 0.0f));

	OnClose.Broadcast();
}

float UOpenDoor::CalculateTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (PressurePlate) // if PressurePlate != nullptr
	{
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	}

	for (auto* a : OverlappingActors)
	{
		UPrimitiveComponent* p = a->FindComponentByClass<UPrimitiveComponent>();
		float mass = p->GetMass();

		FString n = a->GetName();
		FString m = FString::SanitizeFloat(mass);
		UE_LOG(LogTemp, Warning, TEXT("[OpenDoor] Actor[%s] applying [%s]kg of force to pressure pad."), *n, *m);

		TotalMass += mass;
	}

	return TotalMass;
}