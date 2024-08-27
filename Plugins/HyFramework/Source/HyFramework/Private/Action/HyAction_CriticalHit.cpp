// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_CriticalHit.h"
#include "Actors/Character/HyCharacterBase.h"

#include "HyTagSubsystem.h"
#include "HyCoreMacro.h"

#include "ActionsTypes.h"



void UHyAction_CriticalHit::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}


	// Critical Hit은 공격자와 마주보도록, Back은 공격맞은 방향을 보도록
	FVector LastAttackDir = FVector::ZeroVector;
	FRotator InputRotation = FRotator::ZeroRotator;

	// 뒤에서 공격시 Donw 상태로	
	if (InContext == TEXT("Back"))
	{
		LastAttackDir = HyCharacterOwner->GetLastAttackDirection();
		InputRotation.Pitch = 0;
		InputRotation = FRotationMatrix::MakeFromX(LastAttackDir).Rotator();

		MontageSectionName = FName(InContext);

		// To Down 상태로 만들어야하므로 현재 액션이 아닌 donw parent를 넣음
		FGameplayTag DownParent = GET_TAG_SUBSYSTEM()->ActionLocationTagSet.DownActionTag;
		FGameplayTag KeepDownAction = GET_TAG_SUBSYSTEM()->GetActionTypeByDamageType(GET_TAG_SUBSYSTEM()->HitTagSet.DamagedDown, DownParent);
		FActionExcuteData ExcuteAction = FActionExcuteData(KeepDownAction, EActionPriority::EHighest);
		HyCharacterOwner->SetStoredAction(ExcuteAction, "", true);
	}
	else
	{
		LastAttackDir = HyCharacterOwner->GetLastAttackDirection() * -1.f;
		InputRotation.Pitch = 0;
		InputRotation = FRotationMatrix::MakeFromX(LastAttackDir).Rotator();
	}

	HyCharacterOwner->SetActorRotation(InputRotation);

}

void UHyAction_CriticalHit::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_CriticalHit::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_CriticalHit::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

bool UHyAction_CriticalHit::IsStopConditional_Implementation()
{
	return Super::IsStopConditional_Implementation();
}
