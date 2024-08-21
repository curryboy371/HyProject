// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionsBaseAction.h"

#include "HyActionBase.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyActionBase : public UActionsBaseAction
{
	GENERATED_BODY()
	
public:
    virtual void OnActionStarted_Implementation(const FString& InContext = FString());
    virtual void OnActionSetupCompleted_Implementation(const FString& InContext = FString()) {};
    virtual void OnActionEnded_Implementation() {};
    virtual void OnActionTransition_Implementation(class UActionsBaseAction* InpreAction) {};
    virtual void OnTick_Implementation(float DeltaTime) { ActionDuration += DeltaTime; };
    virtual bool IsStopConditional_Implementation() { return true; };
    
    virtual FName GetMontageSectionName_Implementation() { return MontageSectionName; };


protected:
    UPROPERTY()
    TObjectPtr<class AHyCharacterBase> HyCharacterOwner;

    UPROPERTY()
    TObjectPtr<class UHyTagManager> HyTagManager;


    // Action 지속 시간
    float ActionDuration = 0.0f;

    FName MontageSectionName;

};
