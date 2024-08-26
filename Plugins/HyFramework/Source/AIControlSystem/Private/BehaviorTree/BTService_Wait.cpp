// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_Wait.h"
#include "AI/HyAIController.h"
#include "AIControlTypes.h"

#include "Actors/Character/HyCharacterBase.h"
#include "AIControlFunctionLibrary.h"
#include "HyCoreMacro.h"


void UBTService_Wait::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AHyAIController* HyAIController = Cast<AHyAIController>(OwnerComp.GetAIOwner());
	if (!HyAIController)
	{
		ERR_V("HyAIController is nullptr");
		return;
	}

	const APawn* CharacterOwner = HyAIController->GetPawn();
	if (!CharacterOwner)
	{
		ERR_V("CharacterOwner is nullptr");
		return;
	}

	// 1. Combat State 체크
	// 타겟이 거리 내에 있다면  State Combat으로 변경
	if (const AActor* TargetActor = HyAIController->GetTargetActorBBK())
	{
		// lose target 거리 체크
		if (TargetActor->GetDistanceTo(CharacterOwner) < HyAIController->GetLoseTargetDistance())
		{
			HyAIController->SetAIStateBBK(EAIState::ECombat);
			return;
		}
		else
		{
			HyAIController->SetTarget(nullptr);
		}
	}

	// 2. Return Home State 체크
	// homedistane
	if (HyAIController->GetHomeDistanceBBK() > HyAIController->GetHomeRange())
	{
		HyAIController->SetAIStateBBK(EAIState::EReturnHome);
		return;
	}

	// 3. 순찰
	HyAIController->SetAIStateBBK(EAIState::EPatrol);
}
