// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Move.h"
#include "Actors/Character/HyCharacterBase.h"



void UHyAction_Move::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

}

void UHyAction_Move::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);

}

void UHyAction_Move::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

}

void UHyAction_Move::OnActionTransition_Implementation(UActionsBaseAction* InpreAction)
{
	Super::OnActionTransition_Implementation(InpreAction);

}

void UHyAction_Move::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

bool UHyAction_Move::IsStopConditional_Implementation()
{
	return true;
}
