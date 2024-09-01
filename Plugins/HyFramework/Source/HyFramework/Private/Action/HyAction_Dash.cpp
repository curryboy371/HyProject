// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Dash.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"
#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "HyTagSubsystem.h"
#include "HyCoreFunctionLibrary.h"


void UHyAction_Dash::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

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
			// 다음액션 AirStart
			if (InContext == "AirStart")
			{
				HyCharacterOwner->SetStoredAction(GET_TAG_SUBSYSTEM()->ActionTagSet.ActionAirStartAttacking, EActionPriority::EMedium, "AfterDashStart", true);
			}

			bUseCheckTargetMovement = true;
			SetDashWarpTarget();
		}
	}
}

void UHyAction_Dash::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

void UHyAction_Dash::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	HyCharacterOwner->ReleaseWarpingTarget(WarpNameDash);

	LOG_V("%s", *HyCharacterOwner->GetActorLocation().ToString());

}


bool UHyAction_Dash::IsStopConditional_Implementation()
{
	return true;
}

void UHyAction_Dash::OnTargetMovement()
{
	SetDashWarpTarget();
}
