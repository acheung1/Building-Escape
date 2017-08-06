// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPOV.h"


// Sets default values for this component's properties
UCameraPOV::UCameraPOV()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraPOV::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

ATriggerVolume * UCameraPOV::getTrigger()
{
	return trigger;
}


// Called every frame
void UCameraPOV::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

