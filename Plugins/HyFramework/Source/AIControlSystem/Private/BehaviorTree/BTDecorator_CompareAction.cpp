// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTDecorator_CompareAction.h"

#include "AI/HyAIController.h"
#include "Actors/Character/HyCharacterBase.h"

#include "HyCoreMacro.h"




UBTDecorator_CompareAction::UBTDecorator_CompareAction()
{
	CheckActionTags.Reset();
}

bool UBTDecorator_CompareAction::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

	FGameplayTagContainer TagsToCheck;

	FGameplayTag PerformingTag = HyChracter->GetCurAction();

	int32 TagSize = CheckActionTags.Num();
	for (int32 i = 0; i < TagSize; ++i)
	{
		TagsToCheck.AddTag(CheckActionTags[i]);
	}

	bool bRet = TagsToCheck.HasTag(PerformingTag);

	return bRet;
}
