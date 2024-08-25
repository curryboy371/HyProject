// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_KeepDown.h"

#include "Actors/Character/HyCharacterBase.h"

#include "HyTagSubsystem.h"
#include "HyCoreMacro.h"

#include "ActionsTypes.h"


void UHyAction_KeepDown::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

}

void UHyAction_KeepDown::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_KeepDown::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_KeepDown::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}

	if(ActionDuration > HyCharacterOwner->KeepDownTime)
	{
		FGameplayTag KeepDownAction = GET_TAG_SUBSYSTEM()->GetActionTypeByDamageType(GET_TAG_SUBSYSTEM()->HitTagSet.DamagedStanding, ActionTag);
		FActionExcuteData ExcuteAction = FActionExcuteData(KeepDownAction, EActionPriority::EHighest);
		if (HyCharacterOwner->TriggerAction(ExcuteAction, "", true))
		{
			HyCharacterOwner->KeepDownTime = 0.0f;
		}
	}

}

bool UHyAction_KeepDown::IsStopConditional_Implementation()
{
	return false;
}
