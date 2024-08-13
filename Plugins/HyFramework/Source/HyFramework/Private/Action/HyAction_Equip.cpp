// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Equip.h"
#include "Actors/Character/HyCharacterBase.h"



void UHyAction_Equip::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

}

void UHyAction_Equip::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);

}

void UHyAction_Equip::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

	if (HyCharacterOwner)
	{
		HyCharacterOwner->SetCombatMode(true);
	}
}

void UHyAction_Equip::OnActionTransition_Implementation(UActionsBaseAction* InpreAction)
{
	Super::OnActionTransition_Implementation(InpreAction);

}

void UHyAction_Equip::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

bool UHyAction_Equip::IsStopConditional_Implementation()
{
	return true;
}
