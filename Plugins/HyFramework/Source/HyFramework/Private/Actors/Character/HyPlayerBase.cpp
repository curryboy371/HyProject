// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyPlayerBase.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"


#include "HyCoreMacro.h"

bool AHyPlayerBase::FindTarget()
{
	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		ERR_V("HyInst is not set.");
		return false;
	}

	UHySpawnManager* SpawnMgr = Inst->GetManager<UHySpawnManager>();
	if (!SpawnMgr)
	{
		ERR_V("SpawnMgr is not set.");
		return false;
	}

	FVector TargetLocation = FVector::ZeroVector;
	bool bHasTarget = false;
	if (TargetGuid.IsValid())
	{
		// 타겟이 이미 있는경우
		if (SpawnMgr->IsValidCharacterWithLocation(TargetGuid, TargetLocation))
		{
			bHasTarget = true;
		}
	}
	
	if (!bHasTarget)
	{
		if (SpawnMgr->FindTargetMonster(GetActorLocation(), EnableTargetRange, TargetGuid, TargetLocation))
		{
			bHasTarget = true;
		}
	}

	if (bHasTarget)
	{
		return SetCharacterRotationIfInRange(TargetLocation, EnableTargetRange);
	}

	return false;
}
