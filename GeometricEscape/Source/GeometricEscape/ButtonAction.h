// Copyright ToasterCat Productions, LLC.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ButtonAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonActionEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRICESCAPE_API UButtonAction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UButtonAction();

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
	FButtonActionEvent OnButtonPress;
	UPROPERTY(BlueprintAssignable)
	FButtonActionEvent OnButtonRelease;

	///- External API ------------------------------------=
	///
	void Press();
	void Release();

private:
	float TimeSinceLastButtonRelease = 0.f;
};
