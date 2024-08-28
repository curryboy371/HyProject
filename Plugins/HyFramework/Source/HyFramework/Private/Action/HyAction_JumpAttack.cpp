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

	SetJumpAttackWarpTarget();
}

void UHyAction_JumpAttack::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

	if (!HyCharacterOwner)
	{
		return;
	}

	HyCharacterOwner->ReleaseWarpingTarget(WarpNameJumpAttack);
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

void UHyAction_JumpAttack::SetJumpAttackWarpTarget()
{
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return;
	}

	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		ERR_V("Inst  Is nullptr");
		return;
	}

	UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>();
	if(!SpawnManager)
	{
		ERR_V("SpawnManager  Is nullptr");
		return;
	}


	TObjectPtr<UHyCharacterMovementComponent> HyMovementComp = HyCharacterOwner->GetCharacterMovementComp();
	if (!HyMovementComp)
	{
		ERR_V("HyMovementComp  Is nullptr");
		return;
	}

	FVector LandLocation = HyCharacterOwner->GetActorLocation();

	if (HyCharacterOwner->IsTargetAvailable())
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

	LandLocation.Z -= HyMovementComp->GetGroundDistance();
	HyCharacterOwner->SetWarpingTarget(LandLocation, WarpNameJumpAttack);

}
