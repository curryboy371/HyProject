// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Slide.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"
#include "HyTagSubsystem.h"

void UHyAction_Slide::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
}

void UHyAction_Slide::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_Slide::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_Slide::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

bool UHyAction_Slide::IsStopConditional_Implementation()
{
	return true;
}
