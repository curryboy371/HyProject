// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_CriticalHit.h"

void UHyAction_CriticalHit::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
}

void UHyAction_CriticalHit::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_CriticalHit::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_CriticalHit::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

bool UHyAction_CriticalHit::IsStopConditional_Implementation()
{
	return false;
}
