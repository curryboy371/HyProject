// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AirIdle.h"

#include "Actors/Character/HyCharacterBase.h"
#include "Components/HyCharacterMovementComponent.h"

#include "ActionsTypes.h"

#include "HyCoreMacro.h"


void UHyAction_AirIdle::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

	if (HyCharacterOwner)
	{
		HyCharacterMovement = Cast<UHyCharacterMovementComponent>(HyCharacterOwner->GetCharacterMovement());
	}

}

void UHyAction_AirIdle::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);

}

void UHyAction_AirIdle::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();


}

void UHyAction_AirIdle::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);

}

void UHyAction_AirIdle::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return;
	}

	if (!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement  Is nullptr");
		return;
	}

	if (HyCharacterMovement)
	{
		if (HyCharacterMovement->GetGroundDistance() == 0.0f)
		{
			HyCharacterOwner->HandleAction(EActionHandleType::EActionHandle_Stop);
		}
	}
}

bool UHyAction_AirIdle::IsStopConditional_Implementation()
{
	return true;
}
