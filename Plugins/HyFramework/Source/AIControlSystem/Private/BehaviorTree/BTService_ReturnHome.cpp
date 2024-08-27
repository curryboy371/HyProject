// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_ReturnHome.h"

#include "AI/HyAIController.h"
#include "Actors/Character/HyCharacterBase.h"
#include "AIControlFunctionLibrary.h"
#include "HyCoreMacro.h"
#include "HyCoreFunctionLibrary.h"

void UBTService_ReturnHome::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	// 집 도착지 거리를 계속해서 체크해줌
	const float DistanceToTarget = FVector::Distance(CharacterOwner->GetActorLocation(), HyAIController->GetTargetLocationBBK());
	HyAIController->SetTargetDistanceBBK(DistanceToTarget);


	UHyCoreFunctionLibrary::DrawDebugCircle(GetWorld(), CharacterOwner->GetActorLocation(), HyAIController->GetHomeRange(), 32, FColor::Green, 0.5f);
}
