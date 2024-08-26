// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTaskNode_SetRotationToTarget.h"

#include "AI/HyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Actors/Character/HyCharacterBase.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "HyTagSubsystem.h"

#include "HyCoreMacro.h"

EBTNodeResult::Type UBTTaskNode_SetRotationToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	AHyAIController* HyAIController = Cast<AHyAIController>(OwnerComp.GetAIOwner());
	if (!HyAIController)
	{
		ERR_V("HyAIController is nullptr");
		return EBTNodeResult::Type::Failed;
	}
	
	AActor*TargetActor = HyAIController->GetTargetActorBBK();
	if(TargetActor == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	if (CharacterBase->SetCharacterRotationIfInRange(TargetActor->GetActorLocation(), CharacterBase->EnableTargetRange))
	{
		return EBTNodeResult::Type::Succeeded;
	}

	return EBTNodeResult::Type::Failed;
}
