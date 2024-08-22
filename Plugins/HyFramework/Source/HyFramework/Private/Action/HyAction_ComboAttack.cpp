// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_ComboAttack.h"

#include "Actors/Character/HyCharacterBase.h"
#include "ActionsTypes.h"
#include "HyCoreMacro.h"

#include "Game/HyGameInstance.h"
#include "Manager/HyTagManager.h"


bool UHyAction_ComboAttack::IsStopConditional_Implementation()
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return false;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return false;
	}

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return false;
	}

	Super::IsStopConditional_Implementation();

	// 다음동작이 있다면 중지, 없다면 현재 액션의 우선순위를 낮춰 이동 등이 입력될 수 있도록
	if(HyCharacterOwner->IsEmptyStoredAction())
	{
		HyCharacterOwner->SetPerformingActionPriority();
		return false;
	}

	// 공격 액션이 저장되어있다면 콤보를 위해 Free
	if (TagManager->IsAttackAction(HyCharacterOwner->GetStoredAction()))
	{
		HyCharacterOwner->HandleAction(EActionHandleType::EActionHandle_Free);
		return false;
	}
	else
	{
		// 다른 액션이라면 Stop
		return true;
	}
}
