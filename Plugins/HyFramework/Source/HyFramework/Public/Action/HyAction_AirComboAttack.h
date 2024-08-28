// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionComboBase.h"
#include "HyAction_AirComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_AirComboAttack : public UHyActionComboBase
{
	GENERATED_BODY()
public:
	virtual void OnActionStarted_Implementation(const FString& InContext = FString());
	virtual void OnActionSetupCompleted_Implementation(const FString& InContext = FString());
	virtual void OnActionEnded_Implementation();
	virtual void OnActionTransition_Implementation(class UActionsBaseAction* InPreAction);
	virtual void OnTick_Implementation(float DeltaTime);
	//virtual bool IsStopConditional_Implementation();
};
