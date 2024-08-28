// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Dash.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"
#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "HyTagSubsystem.h"


void UHyAction_Dash::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

	if (!HyCharacterOwner)
	{
		return;
	}

	LOG_V("%s", *HyCharacterOwner->GetActorLocation().ToString());

	if (HyCharacterOwner->IsTargetAvailable())
	{
		// 다음액션 AirStart
		if (contextString == "AirStart")
		{
			HyCharacterOwner->SetStoredAction(GET_TAG_SUBSYSTEM()->ActionTagSet.ActionAirStartAttacking, EActionPriority::EMedium, "AfterDashStart", true);
		}

		bUseCheckTargetMovement = true;
		SetDashWarpTarget();
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
