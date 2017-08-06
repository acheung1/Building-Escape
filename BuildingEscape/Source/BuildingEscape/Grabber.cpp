// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	objBeingHeld = false;

	owner = GetOwner();

	FindInputComponent();
	FindPhysicsHandleComponent();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerLocation = owner->GetActorLocation();
	FRotator playerRotation = owner->GetActorRotation();

	// this is where the physics body will be placed once it is grabbed by the player
	FVector objHoldLocation = playerLocation + playerRotation.RotateVector(FVector(200.0f, 0.0f, 200.0f));

	// this is the end of the visual line
	FVector lineEndTrace = playerLocation + playerRotation.RotateVector(FVector(250.0f, 0.0f, -100.0f));

	// visualize a line for the ray cast
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), playerLocation, lineEndTrace, FColor(255, 105, 180), 0.0f, 0.0f);

	// moves the object the physics handle is holding
	if (physicsHandler->GrabbedComponent) {
		physicsHandler->SetTargetLocation(objHoldLocation);
	}

	
} 

// setup physics handle component
// REMINDER: AN ACTOR MUST BE A PHYSICS ACTOR AND MUST BE ABLE TO SIMULATE PHYSICS
void UGrabber::FindPhysicsHandleComponent()
{
	physicsHandler = owner->FindComponentByClass<UPhysicsHandleComponent>();

	if (physicsHandler == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s PHYSICS HANDLE COMPONENT NOT WORKING"), *owner->GetName());
	}
}

// set up input component
void UGrabber::FindInputComponent()
{
	input = owner->FindComponentByClass<UInputComponent>();

	if (input) {
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s GRABBER INPUT COMPONENT NOT WORKING"), *owner->GetName());
	}
}

// grabs a physics actorthat is at the end of the end of the ray cast
// holds onto it as long the input key is pressed down
void UGrabber::Grab()
{
	if (objBeingHeld == false) {
		UE_LOG(LogTemp, Warning, TEXT("GRAB METHOD IS WORKING"));
		// gets the physics actor at the end of the ray cast
		auto hitResult = GetPhysicsBodyInReach();
		auto componentGrab = hitResult.GetComponent();
		auto actorHit = hitResult.GetActor();

		// if an actor is hit, attach a physics handle to it
		if (actorHit) {
			// moves the physics actor to the end of the end of the ray cast
			physicsHandler->GrabComponent(componentGrab, NAME_None, componentGrab->GetOwner()->GetActorLocation(), true);
			objBeingHeld = true;
		}
	}
}

// lets go of the physics actor the player is holding on to 
void UGrabber::Release()
{
	if (objBeingHeld) {
		UE_LOG(LogTemp, Warning, TEXT("RELEASE METHOD IS WORKING"));
		physicsHandler->ReleaseComponent();
		objBeingHeld = false;
	}
}

// checks if a physics actor is hit by the ray cast
const FHitResult UGrabber::GetPhysicsBodyInReach()
{
	FVector playerLocation = owner->GetActorLocation();
	FRotator playerRotation = owner->GetActorRotation();

	// the end of the ray cast 
	FVector lineEndTrace = playerLocation + playerRotation.RotateVector(FVector(250.0f, 0.0f, -100.0f));

	// set up query parameters
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());

	FHitResult hit;

	// ray cast out to reach distance
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		playerLocation,
		lineEndTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams
	);
	// see what the ray hit
	AActor* actorHit = hit.GetActor();

	if (actorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *(actorHit->GetName()));
	}

	return hit;
}

