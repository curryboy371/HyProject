// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTaskNode_ExcuteAction.h"

#include "Actors/Character//HyCharacterBase.h"
#include "AI/HyAIController.h"



UBTTaskNode_ExcuteAction::UBTTaskNode_ExcuteAction()
{
	ActionTag = FGameplayTag::EmptyTag;

	ActionPriority = EActionPriority::EEmpty;

	ActionContext = FString();

}

EBTNodeResult::Type UBTTaskNode_ExcuteAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (CharacterBase->TriggerAction(ActionTag, ActionPriority, ActionContext))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Type::Failed;

}
