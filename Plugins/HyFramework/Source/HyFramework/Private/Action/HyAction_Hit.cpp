// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Hit.h"


#include "Actors/Character/HyCharacterBase.h"

#include "HyCoreMacro.h"

#include "HyTagSubsystem.h"

void UHyAction_Hit::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

}

void UHyAction_Hit::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_Hit::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_Hit::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}



