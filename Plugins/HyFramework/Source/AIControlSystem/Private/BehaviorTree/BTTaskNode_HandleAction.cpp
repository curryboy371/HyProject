// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTaskNode_HandleAction.h"
#include "AI/HyAIController.h"
#include "Actors/Character/HyCharacterBase.h"

UBTTaskNode_HandleAction::UBTTaskNode_HandleAction()
{

}

EBTNodeResult::Type UBTTaskNode_HandleAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type ResultType = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	AHyCharacterBase* CharacterBase = Cast<AHyCharacterBase>(ControllingPawn);
	if (CharacterBase == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	CharacterBase->HandleAction(ActionType, BlendOut);
	return EBTNodeResult::Succeeded;
}
