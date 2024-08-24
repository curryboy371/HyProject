// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Spawn.h"

#include "Actors/Character/HyCharacterBase.h"
#include "Components/ActionsSystemComponent.h"



void UHyAction_Spawn::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
	if (HyCharacterOwner)
	{
		if (TObjectPtr<UActionsSystemComponent> ActionSystem = HyCharacterOwner->GetActionsSystemComp())
		{
			ActionSystem->SetDefaultActinoTag(HyCharacterOwner->QuickActionExcute.Idle);
		}
	}
}

void UHyAction_Spawn::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);

}

void UHyAction_Spawn::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

}

void UHyAction_Spawn::OnActionTransition_Implementation(UActionsBaseAction* InpreAction)
{
	Super::OnActionTransition_Implementation(InpreAction);

}

void UHyAction_Spawn::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

bool UHyAction_Spawn::IsStopConditional_Implementation()
{
	return true;
}
