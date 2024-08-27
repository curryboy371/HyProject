// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Avoid.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"
#include "HyTagSubsystem.h"


void UHyAction_Avoid::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
}

void UHyAction_Avoid::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);
}

void UHyAction_Avoid::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_Avoid::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_Avoid::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

bool UHyAction_Avoid::IsStopConditional_Implementation()
{
	return false;
}
