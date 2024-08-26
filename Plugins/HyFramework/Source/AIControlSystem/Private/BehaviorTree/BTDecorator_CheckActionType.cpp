// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTDecorator_CheckActionType.h"

#include "AI/HyAIController.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyTagSubsystem.h"
#include "HyCoreMacro.h"


UBTDecorator_CheckActionType::UBTDecorator_CheckActionType()
{
	ActionType = EActionType::EActionType_Normal;
}

bool UBTDecorator_CheckActionType::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
	

	switch (ActionType)
	{
	case EActionType::EActionType_Normal:
		return GET_TAG_SUBSYSTEM()->IsNormalAction(HyChracter->GetCurAction());
	case EActionType::EActionType_Doing:
		return GET_TAG_SUBSYSTEM()->IsDoingAction(HyChracter->GetCurAction());
	case EActionType::EActionType_Damaged:
		return GET_TAG_SUBSYSTEM()->IsDamagedAction(HyChracter->GetCurAction());
	case EActionType::EActionType_Attack:
		return GET_TAG_SUBSYSTEM()->IsAttackAction(HyChracter->GetCurAction());
	case EActionType::EActionType_Skill:
		return GET_TAG_SUBSYSTEM()->IsSkillAction(HyChracter->GetCurAction());
	default:
		break;
	}

	return false;
}
