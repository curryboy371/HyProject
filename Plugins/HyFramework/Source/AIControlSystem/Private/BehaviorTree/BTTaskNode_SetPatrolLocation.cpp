// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTaskNode_SetPatrolLocation.h"
#include "Actors/Character//HyCharacterBase.h"
#include "AI/HyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NavigationSystem.h"
#include "HyCoreMacro.h"



UBTTaskNode_SetPatrolLocation::UBTTaskNode_SetPatrolLocation()
{
	PatrolType = EPatrolType::ERandomPoint;
}

EBTNodeResult::Type UBTTaskNode_SetPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (PatrolType == EPatrolType::ERandomPoint)
	{
		// Set Rand;
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		if (!NavSystem)
		{
			ERR_V("NavSystem is nullptr");
			return EBTNodeResult::Type::Failed;
		}

		// TODO 임시 방편
		// AI Controller 에서 Key로처리하도록 수정할 것
		FNavLocation NextPatrolPos;
		if (NavSystem->GetRandomPointInNavigableRadius(CharacterBase->GetActorLocation(), 1000.f, NextPatrolPos))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), NextPatrolPos.Location);
			return ResultType;
		}
	}
	else
	{


		return ResultType;
	}

	return EBTNodeResult::Type::Failed;
}
