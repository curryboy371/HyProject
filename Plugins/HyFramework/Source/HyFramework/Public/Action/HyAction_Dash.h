// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_AttackBase.h"
#include "HyAction_Dash.generated.h"

/**
 *  Attack은 현재 아니지만, Warping 관련 함수를 상속해서 사용하기 위해 UHyAction_AttackBase 상속
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_Dash : public UHyAction_AttackBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionStarted_Implementation(const FString& InContext = "");
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionEnded_Implementation();

	virtual bool IsStopConditional_Implementation();

	virtual void OnTargetMovement(); // TargetMovementCheck에서 타겟이 움직였을때 호출

};
