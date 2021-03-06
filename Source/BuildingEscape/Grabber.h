// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/InputComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	float Reach = 100.f;
	AActor* Player = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	//RayCast and Grab 
	void Grab();

	//Called when grab is released
	void Release();

	//find assumed physics handle
	void FindPhysicsHandleComponent();

	//Setup assumed attached input component
	void SetupInputComponent();

	//Get the line end of the ray cast
	FVector GetLineStart() const;

	//Get the line end of the ray cast
	FVector GetLineEnd() const;

	//Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;
};
