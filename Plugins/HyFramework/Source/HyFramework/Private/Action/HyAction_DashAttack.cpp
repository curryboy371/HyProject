// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_DashAttack.h"

#include "Actors/Character/HyCharacterBase.h"

#include "HyCoreMacro.h"

#include "Game/HyGameInstance.h"

#include "Manager/HySpawnManager.h"



void UHyAction_DashAttack::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}

	HyCharacterOwner->ReleaseWarpingTarget();
	if (HyCharacterOwner->IsTargetAvailable())
	{
		FVector Location;

		if (UHyInst* Inst = UHyInst::Get())
		{
			if (UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>())
			{
				if (AHyCharacterBase* TargetCharacter = SpawnManager->GetCharacterByGuid(HyCharacterOwner->GetTargetGuidRef()))
				{
					if (TargetCharacter->GetClosestCombatArrow(HyCharacterOwner->GetActorLocation(), HyCharacterOwner->DashAttackRange, Location))
					{
						HyCharacterOwner->SetDashWarpingTarget(Location);
					}
				}
			}
		}
	}
}

void UHyAction_DashAttack::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

void UHyAction_DashAttack::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}

	HyCharacterOwner->ReleaseWarpingTarget();

}

bool UHyAction_DashAttack::IsStopConditional_Implementation()
{

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return false;
	}

	Super::IsStopConditional_Implementation();

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
