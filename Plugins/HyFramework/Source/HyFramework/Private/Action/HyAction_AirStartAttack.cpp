// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_AirStartAttack.h"
#include "Actors/Character/HyCharacterBase.h"
#include "HyCoreMacro.h"
#include "HyTagSubsystem.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "Components/ActionsSystemComponent.h"
#include "Components/HyCharacterMovementComponent.h"

#include "HyCoreFunctionLibrary.h"

void UHyAction_AirStartAttack::OnActionStarted_Implementation(const FString& InContext)
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

	if (!HyCharacterOwner)
	{
		return;
	}

	HasTargetAttack = false;
	FirstTargetDistance = 0.0f;
	HyCharacterOwner->SetCharacterCollisionEnable(false);
	HyCharacterOwner->SetCombatArrowCommandQueue();
	SetAirStartWarpTarget();
}

void UHyAction_AirStartAttack::SetAirStartWarpTarget()
{
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

	CharacterMovement->SetMovementMode(EMovementMode::MOVE_Flying);
	// TODO TEMP
	FVector Location = HyCharacterOwner->GetActorLocation();
	Location.Z += HyCharacterOwner->AirAttackHeight;

	HyCharacterOwner->SetWarpingTarget(Location, WarpNameAirStart);

	if (HyCharacterOwner->IsTargetAvailable())
	{
		if (TObjectPtr<AHyCharacterBase> TargetCharacter = SpawnManager->GetCharacterByGuid(HyCharacterOwner->GetTargetGuidRef()))
		{
			FVector TargetDist = TargetCharacter->GetActorLocation() - HyCharacterOwner->GetActorLocation();
			FirstTargetDistance = TargetDist.Length();
			HasTargetAttack = true;
		}
	}
}

void UHyAction_AirStartAttack::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);

}

void UHyAction_AirStartAttack::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}

	if (UCharacterMovementComponent* CharacterMovement = HyCharacterOwner->GetCharacterMovement())
	{
		CharacterMovement->SetMovementMode(EMovementMode::MOVE_Falling);
		CharacterMovement->GravityScale = 1.0f;
	}

	HyCharacterOwner->SetCharacterCollisionEnable(true);
	HyCharacterOwner->ReleaseWarpingTarget(WarpNameAirStart);
}

void UHyAction_AirStartAttack::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);

}

void UHyAction_AirStartAttack::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	if (HasTargetAttack)
	{
		SetTargetAirHitWarLocation();
	}
}

void UHyAction_AirStartAttack::SetTargetAirHitWarLocation()
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
		if (TObjectPtr<AHyCharacterBase> TargetCharacter = SpawnManager->GetCharacterByGuid(HyCharacterOwner->GetTargetGuidRef()))
		{
			FVector NormalForwardDir = HyCharacterOwner->GetActorForwardVector().GetSafeNormal2D();
			FVector TargetAirLocation = HyCharacterOwner->GetActorLocation() + NormalForwardDir * FirstTargetDistance;
			TargetCharacter->SetAirHitWarpLocation(TargetAirLocation);
			UHyCoreFunctionLibrary::DrawArrow(GetWorld(), HyCharacterOwner->GetActorLocation(), TargetAirLocation, 30, FLinearColor::Yellow, 1.f, 1);
		}
	}
}

bool UHyAction_AirStartAttack::IsStopConditional_Implementation()
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
	//else
	//{
	//	// 다른 액션이라면 Stop
	//	return true;
	//}

	return false;
}

void UHyAction_AirStartAttack::OnActionNotify_Implementation()
{
	if (!HyCharacterOwner)
	{
		return;
	}
}
