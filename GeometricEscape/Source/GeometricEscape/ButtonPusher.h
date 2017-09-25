// Copyright ToasterCat Productions, LLC.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#include "ButtonPusher.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRICESCAPE_API UButtonPusher : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UButtonPusher();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
	float ReachLength = 100.f;

	void Push();
	
private:
	UInputComponent* Input = nullptr;
	AActor* LookingAtActor;

	void BindInput();

	const FHitResult GetFirstInteractableInReach();
	FVector CalculateReachLineStart();
	FVector CalculateReachLineEnd();
	void DrawReachLine();
};
