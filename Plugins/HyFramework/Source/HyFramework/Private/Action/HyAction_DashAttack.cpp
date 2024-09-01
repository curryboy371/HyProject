// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_DashAttack.h"

#include "Actors/Character/HyCharacterBase.h"

#include "HyCoreMacro.h"

#include "Game/HyGameInstance.h"

#include "Manager/HySpawnManager.h"



void UHyAction_DashAttack::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}


	if (HyCharacterOwner->IsTargetAvailable())
	{
		bUseCheckTargetMovement = true;
		SetDashWarpTarget();
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

	HyCharacterOwner->ReleaseWarpingTarget("Dash");
}

void UHyAction_DashAttack::OnTargetMovement()
{
	SetDashWarpTarget();
}
