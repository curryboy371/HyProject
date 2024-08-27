// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_Combat.h"

#include "HyCoreMacro.h"
#include "Actors/Character/HyCharacterBase.h"



#include "AIControlFunctionLibrary.h"

#include "AI/HyAIController.h"
#include "HyCoreFunctionLibrary.h"

void UBTService_Combat::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	SpendTime += DeltaSeconds;

	UpdateCombatService(OwnerComp);
}

void UBTService_Combat::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	HyAIController = nullptr;
	TargetActor = nullptr;
	CharacterOwner = nullptr;

    Super::OnSearchStart(SearchData);


	// 타겟이 유효한지 체크

	UpdateCombatService(SearchData.OwnerComp);
}

void UBTService_Combat::UpdateCombatService(UBehaviorTreeComponent& OwnerComp)
{
	HyAIController = Cast<AHyAIController>(OwnerComp.GetAIOwner());
	if (!HyAIController)
	{
		return;
	}

	TargetActor = HyAIController->GetTargetActorBBK();
	if(!TargetActor)
	{
		HyAIController->SetTarget(nullptr);
		return;
	}

	CharacterOwner = Cast<AHyCharacterBase>(HyAIController->GetPawn());

	// lose target 거리 체크
	if (TargetActor->GetDistanceTo(CharacterOwner) > HyAIController->GetLoseTargetDistance())
	{
		HyAIController->SetTarget(nullptr);
		return;
	}


	float CharacterDistance = -1.f;
	ACharacter* TargetChar = Cast<ACharacter>(TargetActor);
	if (TargetChar) 
	{
		CharacterDistance = UAIControlFunctionLibrary::CalcDistanceBetweenCharacter(CharacterOwner, TargetChar);
	}
	
	HyAIController->SetTargetLocationBBK(TargetActor->GetActorLocation());
	HyAIController->SetTargetDistanceBBK(CharacterDistance);

	UHyCoreFunctionLibrary::DrawDebugCircle(GetWorld(), CharacterOwner->GetActorLocation(), HyAIController->GetLoseTargetDistance(), 32, FColor::Red, 0.5f);

}
