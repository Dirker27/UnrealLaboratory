// Copyright ToasterCat Productions, LLC.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ActionReceiver.h"

#include "WallController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWallControllerEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRICESCAPE_API UWallController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallController();

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
	FWallControllerEvent OnRetract;
	UPROPERTY(BlueprintAssignable)
	FWallControllerEvent OnErect;

	///- External API ------------------------------------=
	///
	void TriggerRetract();
	void TriggerErect();

	///- Engine Access --------------------------------------=
	///
	UActionReceiver* ActionReciever = nullptr;
};
