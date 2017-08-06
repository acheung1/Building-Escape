// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"

#define OUT

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
}

void UDoorOpen::OpenDoor()
{
	// calls on blueprint to open door
	onOpen.Broadcast();
}

void UDoorOpen::CloseDoor()
{
	// calls on blueprint to close door
	onClose.Broadcast();
}

// finds the total mass of all actors on the pressure plate
float UDoorOpen::GetMassOnPressurePlate()
{
	float totalMass = 0.0f;

	// array of actors on the pressure plate
	TArray<AActor*> overlapActors;
	pressurePlate->GetOverlappingActors(OUT overlapActors);

	// iterating and adding each actor's mass to the total
	for (auto& actor : overlapActors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s %d"), *actor->GetName(), actor->FindComponentByClass<UPrimitiveComponent>()->GetMass());
	}

	return totalMass;
}

bool UDoorOpen::GetRotateX()
{
	return rotateX;
}

bool UDoorOpen::GetRotateY()
{
	return rotateY;
}

bool UDoorOpen::GetRotateZ	()
{
	return rotateZ;
}

// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// REMAINDER: ACTOR MUST ALLOW SIMULATE PHYSICS, GENERATE HIT(OVERLAP EVENTS AS WELL FOR PAWN) FOR PRESSURE PLATE TO RECOGNIZE IT
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// checks if the pressure plate is triggered by weight or just by placing an actor on it
	if (factorWeight) {
		// if there are enough weight on the pressure plate
		if (GetMassOnPressurePlate() >= pressurePlateMass) {
			OpenDoor();
			lastTimeDoorOpen = GetWorld()->GetTimeSeconds();
		}
	}
	else {
		// if the two actors are overlapping
		if (pressurePlate->IsOverlappingActor(actorOpens)) {
			OpenDoor();
			lastTimeDoorOpen = GetWorld()->GetTimeSeconds();
		}
	}

	// reverts the current owner to closeRotate settings when the delay time is up
	if (GetWorld()->GetTimeSeconds() - lastTimeDoorOpen > timeDelayDoorClose) {
		CloseDoor();
	}
}

