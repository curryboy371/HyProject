// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Crouching.h"
#include "Actors/Character/HyCharacterBase.h"

#include "HyCoreMacro.h"


void UHyAction_Crouching::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
	}

	//Characte Crouch State Change
	if(HyCharacterOwner->IsCrouching())
	{
		HyCharacterOwner->UnCrouch();
	}
	else
	{
		HyCharacterOwner->Crouch();
	}

}

void UHyAction_Crouching::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
	}


}

FName UHyAction_Crouching::GetMontageSectionName_Implementation()
{
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
	}

	if (animMontage)
	{
		int32 MontageIndex = 0;
		if (HyCharacterOwner->IsCrouching())
		{
			MontageIndex = 1;
		}

		const FName SectionName = animMontage->GetSectionName(MontageIndex);

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
