// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/HyAction_AttackBase.h"
#include "HyAction_DashAttack.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAction_DashAttack : public UHyAction_AttackBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActionStarted_Implementation(const FString& InContext = "");
	virtual void OnTick_Implementation(float DeltaTime);
	virtual void OnActionEnded_Implementation();

	virtual void OnTargetMovement(); // TargetMovementCheck에서 타겟이 움직였을때 호출

protected:


};
