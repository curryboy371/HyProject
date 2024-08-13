// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyActionBase.h"

#include "Actors/Character/HyCharacterBase.h"

#include "HyCoreLogging.h"

void UHyActionBase::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

	ActionDuration = 0.0f;

	HyOwnerCharacter = Cast<AHyCharacterBase>(CharacterOwner);

	if (!HyOwnerCharacter)
	{
		ERR_V("HyOwnerCharacter is nullptr");
	}
}
