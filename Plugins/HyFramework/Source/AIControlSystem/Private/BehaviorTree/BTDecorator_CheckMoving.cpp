// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTDecorator_CheckMoving.h"

#include "AI/HyAIController.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyTagSubsystem.h"
#include "HyCoreMacro.h"


bool UBTDecorator_CheckMoving::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	APawn* OwnerPlayer = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPlayer == nullptr)
	{
		ERR_V("OwnerPlayer is invalid");
		return false;
	}

	AHyCharacterBase* HyChracter = Cast<AHyCharacterBase>(OwnerPlayer);
	if (HyChracter == nullptr)
	{
		ERR_V("HyChracter is invalid");
		return false;
	}

	bool IsMoveAction = GET_TAG_SUBSYSTEM()->IsMoveAction(HyChracter->GetCurAction());
	if (IsMoveAction && HyChracter->GetVelocity().Size() > 0.f)
	{
		return true;
	}

	return false;
}
