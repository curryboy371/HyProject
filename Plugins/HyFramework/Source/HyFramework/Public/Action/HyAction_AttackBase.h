// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyAction_AttackBase.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_AttackBase : public UHyActionBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionStarted_Implementation(const FString& contextString = "");
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionEnded_Implementation();

	virtual bool IsStopConditional_Implementation();
};
