// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_KeepDown.h"

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
}

bool UHyAction_KeepDown::IsStopConditional_Implementation()
{
	return false;
}
