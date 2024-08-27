// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_AIMoveTo.h"
#include "AI/HyAIController.h"

#include "Actors/Character/HyCharacterBase.h"

#include "HyTagSubsystem.h"
#include "ActionsTypes.h"

#include "HyCoreMacro.h"

UBTTask_AIMoveTo::UBTTask_AIMoveTo()
{
	NodeName = "TriggerMoveAction";
}

EBTNodeResult::Type UBTTask_AIMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	AHyAIController* HyAIController = Cast<AHyAIController>(OwnerComp.GetAIOwner());
	if (!HyAIController)
	{
		return EBTNodeResult::Type::Failed;
	}


	AHyCharacterBase* CharacterBase = Cast<AHyCharacterBase>(ControllingPawn);
	if (CharacterBase == nullptr)
	{
		ERR_V("CharacterBase is nullptr");
		return EBTNodeResult::Type::Failed;
	}

	if (CharacterBase->TriggerAction(CharacterBase->QuickActionExcute.Move))
	{
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	return EBTNodeResult::Type::Failed;
}
