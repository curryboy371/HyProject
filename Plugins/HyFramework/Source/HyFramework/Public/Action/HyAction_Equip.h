// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyAction_Equip.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_Equip : public UHyActionBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionStarted_Implementation(const FString& InContext = FString());
	virtual void OnActionSetupCompleted_Implementation(const FString& InContext = FString());
	virtual void OnActionEnded_Implementation();
	virtual void OnActionTransition_Implementation(class UActionsBaseAction* InpreAction);
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionNotify_Implementation();

	virtual bool IsStopConditional_Implementation();
	
};
