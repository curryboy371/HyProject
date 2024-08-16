// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyActionBase.h"

#include "Actors/Character/HyCharacterBase.h"
#include "Game/HyGameInstance.h"
#include "Manager/HyTagManager.h"


#include "HyCoreMacro.h"

void UHyActionBase::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

	ActionDuration = 0.0f;

	HyCharacterOwner = Cast<AHyCharacterBase>(CharacterOwner);

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
	}

	if (UHyInst* Inst = UHyInst::Get())
	{
		HyTagManager = Inst->GetManager<UHyTagManager>();
	}

	if (!HyTagManager)
	{
		ERR_V("HyTagManager is nullptr");
	}
}
