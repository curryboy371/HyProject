// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTaskNode_ExcuteAction.h"

#include "Actors/Character//HyCharacterBase.h"
#include "AI/HyAIController.h"

#include "HyCoreMacro.h"

#include "HyTagSubsystem.h"

#include "Navigation/PathFollowingComponent.h"

#include "HyCoreFunctionLibrary.h"

UBTTaskNode_ExcuteAction::UBTTaskNode_ExcuteAction()
{

	NodeName = "TriggerAction";

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
		ERR_V("ControllingPawn is nullptr");
		return EBTNodeResult::Type::Failed;
	}

	AHyAIController* HyAIController = Cast<AHyAIController>(OwnerComp.GetAIOwner());
	if (!HyAIController)
	{
		ERR_V("HyAIController is nullptr");
		return EBTNodeResult::Type::Failed;
	}

	AHyCharacterBase* CharacterBase = Cast<AHyCharacterBase>(ControllingPawn);
	if (CharacterBase == nullptr)
	{
		ERR_V("CharacterBase is nullptr");
		return EBTNodeResult::Type::Failed;
	}

	bool IsMoveAction = GET_TAG_SUBSYSTEM()->IsMoveAction(ActionTag);

	bool IsAttackAction = GET_TAG_SUBSYSTEM()->IsAttackAction(ActionTag);


	// 공격 액션이라면 타겟 방향으로 회전
	if (IsAttackAction)
	{
		if (AActor* TargetActor = HyAIController->GetTargetActorBBK())
		{
			if (!CharacterBase->SetCharacterRotationIfInRange(TargetActor->GetActorLocation(), CharacterBase->EnableTargetRange))
			{
				return EBTNodeResult::Type::Failed;
			}
		}
	}

	if (CharacterBase->TriggerAction(ActionTag, ActionPriority, ActionContext, bCanStore))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Type::Failed;

}
