// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyActionComboBase.h"

#include "HyCoreMacro.h"


void UHyActionComboBase::OnActionStarted_Implementation(const FString& InContext)
{
	bSuccesfulCombo = false;

	Super::OnActionStarted_Implementation(InContext);


}

void UHyActionComboBase::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();

}

void UHyActionComboBase::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);

    if (InPreAction && InPreAction->IsA(GetClass()))
    {
        if (animMontage && CurrentComboIndex > animMontage->CompositeSections.Num())
        {
            CurrentComboIndex = 0;
        }
        else
        {
            CurrentComboIndex++;
        }
        bSuccesfulCombo = true;

    }
	else
	{
		CurrentComboIndex = 0;
		bSuccesfulCombo = false;
	}
}

void UHyActionComboBase::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

FName UHyActionComboBase::GetMontageSectionName_Implementation()
{
    if (animMontage)
    {
        const FName SectionName = animMontage->GetSectionName(CurrentComboIndex);

        if (SectionName != NAME_None)
        {
            return SectionName;
        }
        else
        {
            CurrentComboIndex = 0;
            return animMontage->GetSectionName(CurrentComboIndex);
        }
    }
    return NAME_None;
}

void UHyActionComboBase::ClearCombo()
{
    CurrentComboIndex = 0;
	bSuccesfulCombo = false;
}
