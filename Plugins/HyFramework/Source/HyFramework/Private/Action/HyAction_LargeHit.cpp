// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_LargeHit.h"

void UHyAction_LargeHit::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);


}

void UHyAction_LargeHit::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_LargeHit::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_LargeHit::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

FName UHyAction_LargeHit::GetMontageSectionName_Implementation()
{
	return FName();
}
