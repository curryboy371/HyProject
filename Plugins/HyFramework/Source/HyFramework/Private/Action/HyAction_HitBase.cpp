// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_HitBase.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"


void UHyAction_HitBase::OnActionStarted_Implementation(const FString& InContext)
{
    Super::OnActionStarted_Implementation(InContext);
    MontageSectionName = FName(*InContext);
}

void UHyAction_HitBase::OnActionEnded_Implementation()
{
    Super::OnActionEnded_Implementation();
}

void UHyAction_HitBase::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
    Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_HitBase::OnTick_Implementation(float DeltaTime)
{
    Super::OnTick_Implementation(DeltaTime);

}

bool UHyAction_HitBase::IsStopConditional_Implementation()
{
    if (!HyCharacterOwner)
    {
        ERR_V("HyCharacterOwner  Is nullptr");
        return false;
    }

    HyCharacterOwner->SetPerformingActionPriority(EActionPriority::EMedium);
    return false;
}

