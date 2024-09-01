// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_HitInAir.h"

#include "Actors/Character/HyCharacterBase.h"
#include "Components/HyCharacterMovementComponent.h"
#include "HyTagSubsystem.h"
#include "HyCoreMacro.h"

#include "ActionsTypes.h"

void UHyAction_HitInAir::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
	CharacterFallStart = false;



}

void UHyAction_HitInAir::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();


}

void UHyAction_HitInAir::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);


}

void UHyAction_HitInAir::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	if (!CharacterFallStart)
	{
		if (ActionDuration > 1.f)
		{
			CharacterFallStart = true;

			if (UCharacterMovementComponent* CharacterMovement = HyCharacterOwner->GetCharacterMovement())
			{
				CharacterMovement->SetMovementMode(EMovementMode::MOVE_Falling);
			}
		}
	}
}

bool UHyAction_HitInAir::IsStopConditional_Implementation()
{
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return false;
	}

	HyCharacterOwner->SetPerformingActionPriority(EActionPriority::ELow);
	return false;
}
