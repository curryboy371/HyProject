// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_HitBase.h"
#include "HyAction_LargeHit.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_LargeHit : public UHyAction_HitBase
{
	GENERATED_BODY()
public:
    virtual void OnActionStarted_Implementation(const FString& InContext = FString());
    virtual void OnActionEnded_Implementation();
    virtual void OnActionTransition_Implementation(class UActionsBaseAction* InPreAction);
    virtual void OnTick_Implementation(float DeltaTime);

    virtual FName GetMontageSectionName_Implementation();

protected:
    int32 SectionIndex = 0;
};
