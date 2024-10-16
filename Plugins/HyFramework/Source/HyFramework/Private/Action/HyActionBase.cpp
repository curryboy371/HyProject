// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyActionBase.h"

#include "Actors/Character/HyCharacterBase.h"
#include "Game/HyGameInstance.h"

#include "HyCoreMacro.h"

void UHyActionBase::OnActionStarted_Implementation(const FString& InContext)
{
	bIsAIAction = false;

	MontageSectionName = NAME_None;

	Super::OnActionStarted_Implementation(InContext);

	ActionDuration = 0.0f;

	HyCharacterOwner = Cast<AHyCharacterBase>(CharacterOwner);

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
		return;
	}
	
	bIsAIAction = GET_TAG_SUBSYSTEM()->IsAIPlaying(HyCharacterOwner->GetEquipTag());
}
