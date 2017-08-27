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
	ATriggerVolume* PressurePlate;

private:
	AActor* Owner;

	AActor* WhitelistedActor;
	float LastTimeDoorOpened = 0.0f;

	void Open();
	void Close();
};
