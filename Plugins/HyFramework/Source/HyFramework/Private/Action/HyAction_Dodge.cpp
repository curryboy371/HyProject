// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Dodge.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"
#include "HyTagSubsystem.h"

void UHyAction_Dodge::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
}

void UHyAction_Dodge::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);
}

void UHyAction_Dodge::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

}

void UHyAction_Dodge::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_Dodge::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

bool UHyAction_Dodge::IsStopConditional_Implementation()
{
	return false;
}
