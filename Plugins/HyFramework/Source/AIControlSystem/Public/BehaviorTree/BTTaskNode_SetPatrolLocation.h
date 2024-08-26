// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIControlTypes.h"

#include "BTTaskNode_SetPatrolLocation.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTTaskNode_SetPatrolLocation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_SetPatrolLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	EPatrolType PatrolType = EPatrolType::ERandomPoint;

};
