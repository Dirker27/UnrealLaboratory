// Copyright ToasterCat Productions, LLC.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "WallRetractor.h"

#include "InteriorWallTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteriorWallTriggerEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRICESCAPE_API UInteriorWallTrigger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteriorWallTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	///- Engine Call-ables -------------------------------=
	///
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	///- BluePrint Access --------------------------------=
	///
	UPROPERTY(BlueprintAssignable)
	FInteriorWallTriggerEvent OnTriggerRetract;
	UPROPERTY(BlueprintAssignable)
	FInteriorWallTriggerEvent OnTriggerErect;

	///- Game World Access -------------------------------=
	///
	UPROPERTY(EditAnywhere)
	ATriggerVolume* ActivationPad = nullptr;

	///- External API ------------------------------------=
	///
	// Trigger Wall Retract
	void TriggerRetract();
	// Trigger Wall Erect
	void TriggerErect();

private:
	UWallRetractor* Retractor = nullptr;
};
