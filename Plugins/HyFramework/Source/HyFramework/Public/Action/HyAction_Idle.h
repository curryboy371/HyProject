// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyActionBase.h"
#include "HyAction_Idle.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_Idle : public UHyActionBase
{
	GENERATED_BODY()
	
public:
	UHyAction_Idle()
	{
		CombatModeCooldownTime = 10.f;
	}

	virtual void OnActionStarted_Implementation(const FString& InContext = FString());
	virtual void OnActionSetupCompleted_Implementation(const FString& InContext = FString());
	virtual void OnActionEnded_Implementation();
	virtual void OnActionTransition_Implementation(class UActionsBaseAction* InpreAction);
	virtual void OnTick_Implementation(float DeltaTime);
	virtual bool IsStopConditional_Implementation();
	

protected:
	// 캐릭터가 전투모드에서 비전투모드로 돌아가는 쿨다운 타임
	float CombatModeCooldownTime;
};
