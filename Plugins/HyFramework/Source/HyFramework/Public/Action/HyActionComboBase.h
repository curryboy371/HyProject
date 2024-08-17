// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyActionComboBase.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyActionComboBase : public UHyActionBase
{
	GENERATED_BODY()
	
public:
    virtual void OnActionStarted_Implementation(const FString& InContext = FString());
    virtual void OnActionSetupCompleted_Implementation(const FString& InContext = FString()) {};
    virtual void OnActionEnded_Implementation();
    virtual void OnActionTransition_Implementation(class UActionsBaseAction* InpreAction);
    virtual void OnTick_Implementation(float DeltaTime);
    virtual bool IsStopConditional_Implementation() { return true; };

    virtual FName GetMontageSectionName_Implementation();
public:
    void ClearCombo();

    FORCEINLINE int32 GetComboCounter() const { return CurrentComboIndex; }
    FORCEINLINE bool IsSuccessfulCombo() const { return bSuccesfulCombo; }
    void ResetComboCounter() { CurrentComboIndex = 0; }
    void ForceComboCounter(int32 val) { CurrentComboIndex = val; }

private:
    int32 CurrentComboIndex = 0;
    bool bSuccesfulCombo = false;

};
