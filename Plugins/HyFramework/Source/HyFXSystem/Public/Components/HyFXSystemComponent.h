// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HyActorComponent.h"
#include "HyFXSystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class HYFXSYSTEM_API UHyFXSystemComponent : public UHyActorComponent
{
	GENERATED_BODY()
	
public:
	UHyFXSystemComponent();

	virtual void InitializeHyActorComponent() override;

protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
