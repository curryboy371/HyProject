// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyMonsterBase.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API AHyMonsterBase : public AHyCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHyMonsterBase(const FObjectInitializer& ObjectInitializer);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
