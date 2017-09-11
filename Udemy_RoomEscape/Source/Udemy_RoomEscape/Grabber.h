// Copyright ToasterCat Productions LLC - Please don't steal our shit.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_ROOMESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Project a ray and grab any physics body that intersects
	void Grab();

	// Drop whatever may be grabbed
	void Release();

	void DrawReachLine();

private:
	UPROPERTY(EditAnywhere)
	float ReachLength = 100.0f;
	UPROPERTY(EditAnywhere)
	float GripStrength = 100.0f;

private:
	UInputComponent* Input = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void ValidatePhysicsHandle();
	void BindInput();

	const FHitResult GetFirstPhysicsBodyInReach();
	FVector CalculateReachLineStart();
	FVector CalculateReachLineEnd();
};
