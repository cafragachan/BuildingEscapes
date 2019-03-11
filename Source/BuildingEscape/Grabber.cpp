// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


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

	Player = GetOwner();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if(PhysicsHandle != nullptr){}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing handle component "), *GetOwner()->GetName());
	}

	if (InputComponent != nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found "));
		//bind the input axis

		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing Input component "), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector LookPos;
	FRotator LookRot;
	Player->GetActorEyesViewPoint(LookPos, LookRot);

	FVector LineEnd = LookPos + LookRot.Vector() * Reach;

	DrawDebugLine(GetWorld(), LookPos, LineEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		LookPos,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	AActor* HitActor = Hit.GetActor();

	if(HitActor != nullptr) UE_LOG(LogTemp, Warning, TEXT("HIT: %s"), *Hit.GetActor()->GetName());
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released"));

}

