// Copyright ToasterCat Productions, LLC.

#include "GeometricEdge.h"

#include "ActionReceiver.h"

#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/EngineTypes.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UGeometricEdge::UGeometricEdge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGeometricEdge::BeginPlay()
{
	Super::BeginPlay();

	this->Receiver = GetOwner()->FindComponentByClass<UActionReceiver>();
	if (!this->Receiver)
	{
		UE_LOG(LogTemp, Error, TEXT("[GeometricEdge] Missing required component: ActionReceiver."));
	}

	this->ParticleSystem = GetOwner()->FindComponentByClass<UParticleSystemComponent>();
	if (this->ParticleSystem)
	{
		this->ParticleSystem->DeactivateSystem();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[GeometricEdge] Missing required component: ParticleSystem."));
	}
}


// Called every frame
void UGeometricEdge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->Receiver->IsActive())
	{
		this->ActivateBeam();
	}
}

void UGeometricEdge::ActivateBeam()
{
	if (!this->BeamIsActive)
	{
		this->BeamIsActive = true;
		this->ParticleSystem->ActivateSystem();
	}
}

void UGeometricEdge::DeactivateBeam()
{
	if (this->BeamIsActive)
	{
		this->BeamIsActive = false;
		this->ParticleSystem->DeactivateSystem();
	}
}

