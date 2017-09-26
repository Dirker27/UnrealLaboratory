// Copyright ToasterCat Productions, LLC.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WallRetractor.generated.h"


/*
 * ****************** DEPRECATION NOTICE **************************
 *                Use WallController Instead
 * ****************************************************************
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRICESCAPE_API UWallRetractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallRetractor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	///- Engine Call-ables -------------------------------=
	///
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	///- Public Fields -----------------------------------=
	///
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RetractHeight = 0.f;

	///- External API ------------------------------------=
	///
	// Trigger Wall Retract
	void Retract();
	// Trigger Wall Erect
	void Erect();

private:
	AActor* Owner;
	FVector InitialLocation;
};
