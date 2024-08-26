// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_Patrol.h"

#include "HyCoreMacro.h"
#include "AI/HyAIController.h"


void UBTService_Patrol::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	// 순찰 도착지 거리를 계속해서 체크해줌
	const float DistanceToTarget = FVector::Distance(CharacterOwner->GetActorLocation(), HyAIController->GetTargetLocationBBK());
	HyAIController->SetTargetDistanceBBK(DistanceToTarget);
}
