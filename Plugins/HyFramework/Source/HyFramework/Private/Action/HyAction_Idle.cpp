// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Idle.h"

#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"


void UHyAction_Idle::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
	ResetCombatModeDuration();

}

void UHyAction_Idle::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);

}

void UHyAction_Idle::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();


}

void UHyAction_Idle::OnActionTransition_Implementation(UActionsBaseAction* InpreAction)
{
	Super::OnActionTransition_Implementation(InpreAction);

}

void UHyAction_Idle::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	if (HyCharacterOwner)
	{
		if (HyCharacterOwner->IsCombatMode())
		{
			CombatModeDuration += DeltaTime;

			if (CombatModeDuration > CombatModeCooldownTime)
			{
				HyCharacterOwner->TriggerAction(HyCharacterOwner->QuickActionExcute.UnEquip);
				ResetCombatModeDuration();
			}
		}
		else
		{
			ResetCombatModeDuration();
		}
	}
}

bool UHyAction_Idle::IsStopConditional_Implementation()
{
	return true;
}
