// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyAction_Slide.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_Slide : public UHyActionBase
{
	GENERATED_BODY()
public:
	virtual void OnActionStarted_Implementation(const FString& InContext = FString());
	virtual void OnActionEnded_Implementation();
	virtual void OnActionTransition_Implementation(class UActionsBaseAction* InPreAction);
	virtual void OnTick_Implementation(float DeltaTime);
	virtual bool IsStopConditional_Implementation();
};
