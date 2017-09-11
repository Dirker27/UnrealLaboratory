// Copyright ToasterCat Productions LLC - Please don't steal our shit.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_ROOMESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 85.0f;
	UPROPERTY(EditAnywhere)
	float ClosedAngle = 0.0f;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.5f;
	UPROPERTY(EditAnywhere)
	float TotalTriggerMass = 25.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

private:
	AActor* Owner;

	float LastTimeDoorOpened = 0.0f;

	// Opens door to specified OpenAngle
	void Open();
	// Closes door to specified ClosedAngle
	void Close();

	// Returns pressure plate mass in [kg]
	float CalculateTotalMassOfActorsOnPlate();
};
