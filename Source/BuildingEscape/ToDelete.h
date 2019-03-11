// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToDelete.generated.h"

UCLASS()
class BUILDINGESCAPE_API AToDelete : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToDelete();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
