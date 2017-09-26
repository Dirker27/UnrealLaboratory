// Copyright ToasterCat Productions, LLC.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ButtonAction.h"

#include "ActionReceiver.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRICESCAPE_API UActionReceiver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionReceiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	///- Engine Call-ables -------------------------------=
	///
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	///- BluePrint Access -----------------------------------=
	///
	UPROPERTY(BlueprintAssignable)
	FActionRequest ActionPerform;

	///- Engine Access --------------------------------------=
	///
	UPROPERTY(EditAnywhere)
	AActor* Button = nullptr;

	///- External API ---------------------------------------=
	///
	bool IsActive();

private:
	void BindActions();
	UButtonAction* ButtonAction = nullptr;
};
