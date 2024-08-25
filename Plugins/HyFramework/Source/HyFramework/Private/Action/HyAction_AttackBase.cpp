// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AttackBase.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"


void UHyAction_AttackBase::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);
}

void UHyAction_AttackBase::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

void UHyAction_AttackBase::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

bool UHyAction_AttackBase::IsStopConditional_Implementation()
{
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return false;
	}

	Super::IsStopConditional_Implementation();

	// 다음동작이 있다면 중지, 없다면 현재 액션의 우선순위를 낮춰 이동 등이 입력될 수 있도록
	if (HyCharacterOwner->IsEmptyStoredAction())
	{
		HyCharacterOwner->SetPerformingActionPriority();
		return false;
	}

	// 공격 액션이 저장되어있다면 콤보를 위해 Free
	if (GET_TAG_SUBSYSTEM()->IsAttackAction(HyCharacterOwner->GetStoredAction()))
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
