// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/ActorComponent.h"
#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

	// get the total mass of actors on the pressure plate
	float GetMassOnPressurePlate();
	
	// returns what axis to rotate over
	UFUNCTION(BlueprintCallable, Category = "RotateAxis")
	bool GetRotateX();

	UFUNCTION(BlueprintCallable, Category = "RotateAxis")
	bool GetRotateY();

	UFUNCTION(BlueprintCallable, Category = "RotateAxis")
	bool GetRotateZ();

	// using blueprints to open the door with animation
	UPROPERTY(BlueprintAssignable)
		FDoorEvent onOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent onClose;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// UPROPERTY to allow flexiblity in the UE editor
	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlate = nullptr; 

	UPROPERTY(EditAnywhere)
		AActor* actorOpens = nullptr; // pawn inherits from actor

	UPROPERTY(EditAnywhere)
		float pressurePlateMass; // the mass of actors on the pressure plate must be >= this number  

	UPROPERTY(EditAnywhere)
		bool factorWeight; // true if mass is a factor in triggering the pressure plate, false if only an actor is needed to trigger it

	// delay time for when the door should start closing
	UPROPERTY(EditAnywhere)
		float timeDelayDoorClose = 1.0f; // delay for closing door 
	
	// what axis to rotate actor over
	UPROPERTY(EditAnywhere)
		bool rotateX;

	UPROPERTY(EditAnywhere)
		bool rotateY;

	UPROPERTY(EditAnywhere)
		bool rotateZ;

	// used for delay
	float lastTimeDoorOpen;

	AActor* owner = nullptr; // refers to the current owner that we want to open/ close upon the overlapping of two actors

};
