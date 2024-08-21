// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Jump.h"
#include "Actors/Character/HyCharacterBase.h"

#include "ActionsTypes.h"
#include "Components/HyCharacterMovementComponent.h"



void UHyAction_Jump::OnActionStarted_Implementation(const FString& InContext)
{
    Super::OnActionStarted_Implementation(InContext);
    if (HyCharacterOwner)
    {
        HyCharacterOwner->Jump();
    }
}

void UHyAction_Jump::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);
}

void UHyAction_Jump::OnActionEnded_Implementation()
{
   	Super::OnActionEnded_Implementation();
}

void UHyAction_Jump::OnActionTransition_Implementation(UActionsBaseAction* InpreAction)
{
    Super::OnActionTransition_Implementation(InpreAction);
}

void UHyAction_Jump::OnTick_Implementation(float DeltaTime)
{
   	Super::OnTick_Implementation(DeltaTime);

    if (HyCharacterOwner && HyCharacterOwner->GetCharacterMovementComp())
    {
        if (HyCharacterOwner->GetCharacterMovementComp()->GetGroundDistance() == 0.0f)
        {
            HyCharacterOwner->HandleAction(EActionHandleType::EActionHandle_Stop);
        }
    }
	
}

bool UHyAction_Jump::IsStopConditional_Implementation()
{
    return true;
}
