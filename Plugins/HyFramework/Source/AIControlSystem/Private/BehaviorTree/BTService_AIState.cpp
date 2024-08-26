// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_AIState.h"

#include "HyCoreMacro.h"
#include "Actors/Character/HyCharacterBase.h"
#include "AIControlFunctionLibrary.h"
#include "AI/HyAIController.h"


UBTService_AIState::UBTService_AIState()
{
}

void UBTService_AIState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	// HomeDistance 설정
	float HomeDistance = FVector::Distance(CharacterOwner->GetActorLocation(), HyAIController->GetHomeLocation());
	HyAIController->SetHomeDistanceBBK(HomeDistance);

	// 2....


}
