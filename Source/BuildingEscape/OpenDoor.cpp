// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include"GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Find the owning Actor
    Owner = GetOwner();
	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Pressure Plate is NUll"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the trigger volume every frame
	if (GetTotalMassOnPlate() >= TriggerMass)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}


float UOpenDoor::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> ActorsOnPlate;
	TArray<UPrimitiveComponent*> OverlappingComponents;

	if (PressurePlate == nullptr) return TotalMass;
	PressurePlate->GetOverlappingActors(ActorsOnPlate);

	for (const auto* Actor : ActorsOnPlate) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor onPlate:  %s"), *Actor->GetName());
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

