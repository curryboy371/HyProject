// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_ComboAttack.h"

#include "Actors/Character/HyCharacterBase.h"
#include "ActionsTypes.h"
#include "HyCoreMacro.h"


bool UHyAction_ComboAttack::IsStopConditional_Implementation()
{
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner  Is nullptr");
		return false;
	}

	Super::IsStopConditional_Implementation();

	HyCharacterOwner->SetPerformingActionPriority();

    return false;
}
