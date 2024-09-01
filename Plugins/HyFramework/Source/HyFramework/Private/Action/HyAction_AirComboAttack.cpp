// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AirComboAttack.h"

#include "Components/HyCharacterMovementComponent.h"

#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"
#include "HyTagSubsystem.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "HyCoreFunctionLibrary.h"



void UHyAction_AirComboAttack::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

	if (!HyCharacterOwner)
	{
		return;
	}

	UCharacterMovementComponent* CharacterMovement = HyCharacterOwner->GetCharacterMovement();
	if (!CharacterMovement)
	{
		return;
	}

	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		return;
	}

	UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>();
	if (!SpawnManager)
	{
		return;
	}

	HyCharacterOwner->SetCharacterCollisionEnable(false);

	if (AHyCharacterBase* TargetCharacter = SpawnManager->GetCharacterByGuid(HyCharacterOwner->GetTargetGuidRef()))
	{
		float TargetDistance = UHyCoreFunctionLibrary::CalcDistanceBetweenCharacter(HyCharacterOwner, TargetCharacter);
		FVector TargetDir = TargetCharacter->GetActorLocation() - HyCharacterOwner->GetActorLocation();
		float DistanceLength = TargetDir.Size();
		if (TargetDistance <= 0.0f)
		{
			TargetDistance = 1.f;
		}

		if (DistanceLength < HyCharacterOwner->DashAttackRange)
		{
			if (HyCharacterOwner->GetNextCombatArrowCommand(CommandDirection))
			{
				bUseCheckTargetMovement = true;
				SetAirDashWarpTarget();
			}
		}
	}

	CharacterMovement->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UHyAction_AirComboAttack::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);
}

void UHyAction_AirComboAttack::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	if (!HyCharacterOwner)
	{
		return;
	}

	UCharacterMovementComponent* CharacterMovement = HyCharacterOwner->GetCharacterMovement();
	if (!CharacterMovement)
	{
		return;
	}
	
	HyCharacterOwner->SetCharacterCollisionEnable(true);

	CharacterMovement->SetMovementMode(EMovementMode::MOVE_Falling);
}

void UHyAction_AirComboAttack::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_AirComboAttack::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

void UHyAction_AirComboAttack::SetAirDashWarpTarget()
{
	if (!HyCharacterOwner)
	{
		return;
	}

	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		return;
	}

	UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>();
	if (!SpawnManager)
	{
		return;
	}

	if (AHyCharacterBase* TargetCharacter = SpawnManager->GetCharacterByGuid(HyCharacterOwner->GetTargetGuidRef()))
	{
		FVector ArrowLocation;

		if (TargetCharacter->GetCombatArrowLocation(CommandDirection, ArrowLocation))
		{
			FVector TargetDir = ArrowLocation - HyCharacterOwner->GetActorLocation();
			float DistanceLength = TargetDir.Size();

			if (DistanceLength < HyCharacterOwner->DashAttackRange)
			{
				FVector NormalDir = TargetDir.GetSafeNormal();
				FVector DashLocation = HyCharacterOwner->GetActorLocation() + NormalDir * DistanceLength;

				HyCharacterOwner->SetWarpingTarget(DashLocation, WarpNameDash);
				LastTargetLocation = TargetCharacter->GetActorLocation();
			}
		}
	}
}

void UHyAction_AirComboAttack::OnTargetMovement()
{
	SetAirDashWarpTarget();
}

//bool UHyAction_AirComboAttack::IsStopConditional_Implementation()
//{
//	if (!HyCharacterOwner)
//	{
//		ERR_V("HyCharacterOwner  Is nullptr");
//		return false;
//	}
//
//	Super::IsStopConditional_Implementation();
//
//	// 다음동작이 있다면 중지, 없다면 현재 액션의 우선순위를 낮춰 이동 등이 입력될 수 있도록
//	if (HyCharacterOwner->IsEmptyStoredAction())
//	{
//		HyCharacterOwner->SetPerformingActionPriority();
//		return false;
//	}
//
//	// 공격 액션이 저장되어있다면 콤보를 위해 Free
//	if (GET_TAG_SUBSYSTEM()->IsAttackAction(HyCharacterOwner->GetStoredAction()))
//	{
//		HyCharacterOwner->HandleAction(EActionHandleType::EActionHandle_Free);
//		return false;
//	}
//	//else
//	//{
//	//	// 다른 액션이라면 Stop
//	//	return true;
//	//}
//
//	return false;
//}
