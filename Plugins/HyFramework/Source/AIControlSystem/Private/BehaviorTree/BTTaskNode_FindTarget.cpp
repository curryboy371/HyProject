// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTaskNode_FindTarget.h"
#include "AI/HyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Actors/Character/HyCharacterBase.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "HyTagSubsystem.h"

#include "HyCoreMacro.h"


UBTTaskNode_FindTarget::UBTTaskNode_FindTarget()
{


}


EBTNodeResult::Type UBTTaskNode_FindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type ResultType = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	AHyCharacterBase* HyCharacter = Cast<AHyCharacterBase>(ControllingPawn);
	if (!HyCharacter)
	{
		ERR_V("HyCharacter is invalid");
		return EBTNodeResult::Type::Failed;
	}

	if (!HyCharacter->IsTargetAvailable())
	{
		HyCharacter->FindTarget();
	}


	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is invalid");
		return EBTNodeResult::Type::Failed;
	}

	UHySpawnManager* SpawnManager = HyInst->GetManager<UHySpawnManager>();
	if(!SpawnManager)
	{
		ERR_V("SpawnManager is invalid");
		return EBTNodeResult::Type::Failed;
	}

	FVector TargetLocation;
	if (!SpawnManager->IsValidCharacterWithLocation(HyCharacter->GetTargetGuidRef(), TargetLocation))
	{
		return EBTNodeResult::Type::Failed;
	}

	return ResultType;
}