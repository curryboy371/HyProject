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
						LastTargetLocation = TargetCharacter->GetActorLocation();
						HyCharacterOwner->SetWarpingTarget(Location, TEXT("Dash"));
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

void UHyAction_DashAttack::TargetMovementCheck()
{
	if (!HyCharacterOwner)
	{
		return;
	}

	if (HyCharacterOwner->IsTargetAvailable())
	{
		FVector Location;

		if (UHyInst* Inst = UHyInst::Get())
		{
			if (UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>())
			{
				if (AHyCharacterBase* TargetCharacter = SpawnManager->GetCharacterByGuid(HyCharacterOwner->GetTargetGuidRef()))
				{
					FVector MoveDir = LastTargetLocation - TargetCharacter->GetActorLocation();
					if (MoveDir.IsNearlyZero(0.1f) == false)
					{
						if (TargetCharacter->GetClosestCombatArrow(HyCharacterOwner->GetActorLocation(), HyCharacterOwner->DashAttackRange, Location))
						{
							LastTargetLocation = TargetCharacter->GetActorLocation();
							HyCharacterOwner->SetWarpingTarget(Location, TEXT("Dash"));
						}
					}
				}
			}
		}
	}
}
