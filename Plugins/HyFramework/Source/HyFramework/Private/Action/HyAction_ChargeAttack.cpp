// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_ChargeAttack.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

#include "Actors/Character/HyCharacterBase.h"
#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"


void UHyAction_ChargeAttack::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}

	SectionIndex = FMath::RandRange(0, 5); // Rand;

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
						HyCharacterOwner->SetWarpingTarget(Location, TEXT("Dash"));
						LastTargetLocation = TargetCharacter->GetActorLocation();
					}
				}
			}
		}
	}
}

void UHyAction_ChargeAttack::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}

	HyCharacterOwner->ReleaseWarpingTarget();

}

void UHyAction_ChargeAttack::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_ChargeAttack::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

FName UHyAction_ChargeAttack::GetMontageSectionName_Implementation()
{
    if (animMontage)
    {
        const FName SectionName = animMontage->GetSectionName(SectionIndex);

        if (SectionName != NAME_None)
        {
            return SectionName;
        }
        else
        {
            return animMontage->GetSectionName(0);
        }
    }
    return NAME_None;
}

void UHyAction_ChargeAttack::TargetMovementCheck()
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
