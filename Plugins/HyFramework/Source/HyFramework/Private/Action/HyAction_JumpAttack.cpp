// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_JumpAttack.h"


#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "Actors/Character/HyCharacterBase.h"
#include "Components/HyCharacterMovementComponent.h"
#include "HyCoreMacro.h"

#include "HyTagSubsystem.h"



void UHyAction_JumpAttack::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return;
	}

	HyCharacterOwner->ReleaseWarpingTarget();
	FVector LandLocation = HyCharacterOwner->GetActorLocation();

	if (TObjectPtr<class UHyCharacterMovementComponent> HyMovement = HyCharacterOwner->GetCharacterMovementComp())
	{
		if (HyCharacterOwner->IsTargetAvailable())
		{
			if (UHyInst* Inst = UHyInst::Get())
			{
				if (UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>())
				{
					if (AHyCharacterBase* TargetCharacter = SpawnManager->GetCharacterByGuid(HyCharacterOwner->GetTargetGuidRef()))
					{
						FVector TargetLocation = TargetCharacter->GetActorLocation();
						FVector Dist = HyCharacterOwner->GetActorLocation() - TargetLocation;
						if (Dist.Length() < 300.f)
						{
							LandLocation.X = TargetLocation.X;
							LandLocation.Y = TargetLocation.Y;
						}
					}
				}
			}
		}

		LandLocation.Z -= HyMovement->GetGroundDistance();
		HyCharacterOwner->SetWarpingTarget(LandLocation, TEXT("Jump"));
	}
}

void UHyAction_JumpAttack::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();


}

void UHyAction_JumpAttack::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);


}

void UHyAction_JumpAttack::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);


}

bool UHyAction_JumpAttack::IsStopConditional_Implementation()
{
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return false;
	}

	Super::IsStopConditional_Implementation();

	// 다음동작이 있는 경우에만 중지
	return !HyCharacterOwner->IsEmptyStoredAction();
}

void UHyAction_JumpAttack::TargetMovementCheck()
{
	// 여기는 추적 x
}
