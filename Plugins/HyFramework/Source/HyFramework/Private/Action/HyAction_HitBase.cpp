// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_HitBase.h"

void UHyAction_HitBase::OnActionStarted_Implementation(const FString& InContext)
{
    Super::OnActionStarted_Implementation(InContext);
    MontageSectionName = FName(*InContext);
}

void UHyAction_HitBase::OnActionEnded_Implementation()
{
    Super::OnActionEnded_Implementation();
}

void UHyAction_HitBase::OnActionTransition_Implementation(UActionsBaseAction* InpreAction)
{
    Super::OnActionTransition_Implementation(InpreAction);
}

void UHyAction_HitBase::OnTick_Implementation(float DeltaTime)
{
    Super::OnTick_Implementation(DeltaTime);

}

