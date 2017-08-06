// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "CollisionQueryParams.h"
#include "Runtime/Engine/Classes//PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
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

private:
	// find components
	void FindPhysicsHandleComponent();
	void FindInputComponent();

	// ray cast and grab whatever is in reach
	void Grab();
	void Release();

	// determines if a physics body is being held
	bool objBeingHeld;

	// gets what object that ray cast hits
	const FHitResult GetPhysicsBodyInReach();

	// current owner
	AActor* owner = nullptr;

	UInputComponent* input = nullptr;
	UPhysicsHandleComponent* physicsHandler = nullptr;
		
	
};
