// Copyright ToasterCat Productions, LLC.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ActionReceiver.h"

#include "GeometricEdge.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRICESCAPE_API UGeometricEdge : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeometricEdge();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateBeam();
	void DeactivateBeam();

private:
	bool BeamIsActive = false;
	UParticleSystemComponent* ParticleSystem = nullptr;
	UActionReceiver* Receiver = nullptr;
};
