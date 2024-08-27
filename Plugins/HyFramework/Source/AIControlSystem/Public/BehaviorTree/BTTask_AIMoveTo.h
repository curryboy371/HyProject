// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_AIMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTTask_AIMoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UBTTask_AIMoveTo();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
