// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindTarget.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTTaskNode_FindTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_FindTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
