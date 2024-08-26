// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetRotationToTarget.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTTaskNode_SetRotationToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	//UBTTaskNode_SetRotationToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
