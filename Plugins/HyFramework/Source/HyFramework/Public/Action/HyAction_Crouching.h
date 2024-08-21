// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyAction_Crouching.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_Crouching : public UHyActionBase
{
	GENERATED_BODY()
public:
    virtual void OnActionStarted_Implementation(const FString& InContext = FString());
    virtual void OnActionEnded_Implementation();

	virtual FName GetMontageSectionName_Implementation();

	
protected:
	bool bIsCrouching;
};
