// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_HitAirLaunch.h"
#include "Actors/Character/HyCharacterBase.h"
#include "Components/HyCharacterMovementComponent.h"


#include "HyTagSubsystem.h"
#include "HyCoreMacro.h"

#include "ActionsTypes.h"

void UHyAction_HitAirLaunch::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}

	// Air Hit은 공격자와 마주보도록
	FVector LastAttackDir = FVector::ZeroVector;
	FRotator InputRotation = FRotator::ZeroRotator;

	LastAttackDir = HyCharacterOwner->GetLastAttackDirection() * -1.f;
	InputRotation.Pitch = 0;
	InputRotation = FRotationMatrix::MakeFromX(LastAttackDir).Rotator();
	HyCharacterOwner->SetActorRotation(InputRotation);

	if (UCharacterMovementComponent* CharacterMovement = HyCharacterOwner->GetCharacterMovement())
	{
		CharacterMovement->SetMovementMode(EMovementMode::MOVE_Flying);
		CharacterMovement->GravityScale = 1.0f;
	}

	HyCharacterOwner->SetWarpingTarget(HyCharacterOwner->GetAirHitWarpLocation(), AirHitWarpName);

	// 다음 액션 저장
	FGameplayTag KeepDownAction = GET_TAG_SUBSYSTEM()->GetActionTypeByDamageType(GET_TAG_SUBSYSTEM()->HitTagSet.DamagedInAir, ActionTag);
	FActionExcuteData ExcuteAction = FActionExcuteData(KeepDownAction, EActionPriority::EMedium);
	HyCharacterOwner->SetStoredAction(ExcuteAction, "", true);
}

void UHyAction_HitAirLaunch::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	if (!HyCharacterOwner)
	{
		return;
	}

	FVector ZeroVec = FVector::ZeroVector;
	HyCharacterOwner->SetAirHitWarpLocation(ZeroVec);
	HyCharacterOwner->ReleaseWarpingTarget(AirHitWarpName);
}

void UHyAction_HitAirLaunch::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_HitAirLaunch::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	if (!HyCharacterOwner)
	{
		return;
	}

	HyCharacterOwner->SetWarpingTarget(HyCharacterOwner->GetAirHitWarpLocation(), AirHitWarpName);
}
