// Copyright ToasterCat Productions, LLC.

#include "InteriorWallTrigger.h"

#define OUT

/*
* ****************** DEPRECATION NOTICE **************************
*                Use WallController Instead
* ****************************************************************
*/

UInteriorWallTrigger::UInteriorWallTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteriorWallTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (!ActivationPad)
	{
		UE_LOG(LogTemp, Error, TEXT("[InteriorWallTrigger] Missing required component: ActivationPad"));
	}

	Retractor = GetOwner()->FindComponentByClass<UWallRetractor>();
	if (!Retractor)
	{
		UE_LOG(LogTemp, Error, TEXT("[InteriorWallTrigger] Missing required component: WallRetractor"));
	}
}

void UInteriorWallTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActivationPad)
	{
		TArray<AActor*> OverlappingActors;
		ActivationPad->GetOverlappingActors(OUT OverlappingActors);

		if (OverlappingActors.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("[InteriorWallTrigger] Initiating Retract!"));
			OnTriggerRetract.Broadcast();

			/*if (Retractor)
			{
				Retractor->Retract();
			}*/
		}
	}
}


void UInteriorWallTrigger::TriggerRetract()
{
	OnTriggerRetract.Broadcast();
}

void UInteriorWallTrigger::TriggerErect()
{
	OnTriggerErect.Broadcast();
}