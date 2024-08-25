// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Standing.h"

void UHyAction_Standing::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
}

void UHyAction_Standing::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_Standing::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_Standing::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

bool UHyAction_Standing::IsStopConditional_Implementation()
{
	return false;
}
