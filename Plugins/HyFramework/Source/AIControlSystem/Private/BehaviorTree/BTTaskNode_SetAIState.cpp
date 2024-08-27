// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTaskNode_SetAIState.h"

#include "AI/HyAIController.h"
#include "HyCoreMacro.h"


UBTTaskNode_SetAIState::UBTTaskNode_SetAIState()
{
	AIState = EAIState::EWait;

}

EBTNodeResult::Type UBTTaskNode_SetAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type ResultType = Super::ExecuteTask(OwnerComp, NodeMemory);

	AHyAIController* HyAIController = Cast<AHyAIController>(OwnerComp.GetAIOwner());
	if (!HyAIController)
	{
		ERR_V("HyAIController is nullptr");
		return EBTNodeResult::Type::Failed;
	}

	HyAIController->SetAIStateBBK(AIState);

	return EBTNodeResult::Succeeded;
}
