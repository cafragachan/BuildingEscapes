// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

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
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent) PhysicsHandle->SetTargetLocation(GetLineEnd());
}

void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto HitActor = HitResult.GetActor();

	if(HitActor != nullptr) PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr) UE_LOG(LogTemp, Error, TEXT("%s missing handle component "), *GetOwner()->GetName());
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent != nullptr)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Input component "), *GetOwner()->GetName());
	}
}

FVector UGrabber::GetLineStart() const
{
	FVector LookPos;
	FRotator LookRot;
	Player->GetActorEyesViewPoint(LookPos, LookRot);

	return LookPos;
}

FVector UGrabber::GetLineEnd() const
{
	FVector LookPos;
	FRotator LookRot;
	Player->GetActorEyesViewPoint(LookPos, LookRot);
	FVector LineEnd = LookPos + LookRot.Vector() * Reach;

	return LineEnd;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetLineStart(),
		GetLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	AActor* HitActor = Hit.GetActor();
	if (HitActor != nullptr) UE_LOG(LogTemp, Warning, TEXT("HIT: %s"), *Hit.GetActor()->GetName());

	return Hit;
}

