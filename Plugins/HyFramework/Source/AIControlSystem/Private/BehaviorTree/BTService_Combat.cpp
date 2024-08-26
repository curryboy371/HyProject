// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_Combat.h"

#include "HyCoreMacro.h"
#include "Actors/Character/HyCharacterBase.h"



#include "AIControlFunctionLibrary.h"

#include "AI/HyAIController.h"

void UBTService_Combat::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UpdateCombatService(OwnerComp);
}

void UBTService_Combat::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	HyAIController = nullptr;
	TargetActor = nullptr;
	CharacterOwner = nullptr;


	// 여기서는 타겟이 유효한지 체크해서
	
	// UpdateCombat


    Super::OnSearchStart(SearchData);

	UpdateCombatService(SearchData.OwnerComp);
}

void UBTService_Combat::UpdateCombatService(UBehaviorTreeComponent& OwnerComp)
{
	HyAIController = Cast<AHyAIController>(OwnerComp.GetAIOwner());
	if (!HyAIController)
	{
		ERR_V("HyAIController is nullptr");
		return;
	}

	TargetActor = HyAIController->GetTargetActorBBK();
	if(!TargetActor)
	{
		ERR_V("TargetActor is nullptr");
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
	
	HyAIController->SetTargetDistanceBBK(CharacterDistance);


}
