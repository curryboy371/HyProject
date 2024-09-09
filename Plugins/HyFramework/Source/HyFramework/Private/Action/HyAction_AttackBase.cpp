// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AttackBase.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"

#include "HyTagSubsystem.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "HyCoreFunctionLibrary.h"


void UHyAction_AttackBase::OnActionStarted_Implementation(const FString& InContext)
{
	bUseCheckTargetMovement = false;

	Super::OnActionStarted_Implementation(InContext);
}

void UHyAction_AttackBase::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
	TargetMovementCheckInterval += DeltaTime;

	if (TargetMovementCheckInterval > MovementCheckDelay)
	{
		TargetMovementCheck();
		TargetMovementCheckInterval = 0.0f;
	}
}

void UHyAction_AttackBase::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

bool UHyAction_AttackBase::IsStopConditional_Implementation()
{
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return false;
	}

	//Super::IsStopConditional_Implementation();

	// 다음동작이 있다면 중지, 없다면 현재 액션의 우선순위를 낮춰 이동 등이 입력될 수 있도록
	if (HyCharacterOwner->IsEmptyStoredAction())
	{
		HyCharacterOwner->SetPerformingActionPriority();
		return false;
	}

	// 공격 액션이 저장되어있다면 콤보를 위해 Free
	if (GET_TAG_SUBSYSTEM()->IsAttackAction(HyCharacterOwner->GetStoredAction()))
	{
		HyCharacterOwner->HandleAction(EActionHandleType::EActionHandle_Free);
		return false;
	}
	else
	{
		// 다른 액션이라면 Stop
		return true;
	}

}

void UHyAction_AttackBase::TargetMovementCheck()
{
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

	if (HyCharacterOwner->IsTargetAvailable())
	{
		FVector Location;
		if (AHyCharacterBase* TargetCharacter = SpawnManager->GetCharacterByGuid(HyCharacterOwner->GetTargetGuidRef()))
		{
			FVector MoveDir = LastTargetLocation - TargetCharacter->GetActorLocation();
			if (MoveDir.IsNearlyZero(0.1f) == false)
			{
				OnTargetMovement();
			}
		}
	}
}

void UHyAction_AttackBase::SetDashWarpTarget()
{
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
		float TargetDistance = UHyCoreFunctionLibrary::CalcDistanceBetweenCharacter(HyCharacterOwner, TargetCharacter);
		FVector TargetDir = TargetCharacter->GetActorLocation() - HyCharacterOwner->GetActorLocation();
		float DistanceLength = TargetDir.Size();

		if (TargetDistance <= 0.0f)
		{
			TargetDistance = 1.f;
		}

		if (DistanceLength < HyCharacterOwner->DashAttackRange)
		{
			
			FVector NormalDir = TargetDir.GetSafeNormal2D();

			FVector DashLocation = HyCharacterOwner->GetActorLocation() + NormalDir * TargetDistance;

			HyCharacterOwner->SetWarpingTarget(DashLocation, WarpNameDash);
			LastTargetLocation = TargetCharacter->GetActorLocation();
		}
	}
}
