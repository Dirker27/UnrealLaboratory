// Copyright ToasterCat Productions, LLC.

#include "ActionReceiver.h"

#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UActionReceiver::UActionReceiver()
{
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UActionReceiver::BeginPlay()
{
	Super::BeginPlay();

	this->BindActions();
}


// Called every frame
void UActionReceiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->IsActive())
	{
		ActionPerform.Broadcast();
	}
}

void UActionReceiver::BindActions()
{
	if (Button)
	{
		this->ButtonAction = Button->FindComponentByClass<UButtonAction>();
		if (!ButtonAction)
		{
			UE_LOG(LogTemp, Error, TEXT("[ActionReciever] Illegal Binding: Your Button isn't a Button."));
		}
	}
}

bool UActionReceiver::IsActive()
{
	bool Active = false;
	if (this->ButtonAction)
	{
		Active |= this->ButtonAction->IsPressed();
	}

	return Active;
}