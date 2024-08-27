// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_LargeHit.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"


#include "Actors/Character/HyCharacterBase.h"

#include "HyCoreMacro.h"

#include "HyTagSubsystem.h"

void UHyAction_LargeHit::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

    SectionIndex = FMath::RandRange(0, 1); // Rand;

    if (HyCharacterOwner)
    {
        // LargeHit은 항상 공격자와 마주보도록
        FVector LastAttackDir = HyCharacterOwner->GetLastAttackDirection() * 1.f;

        FRotator InputRotation = FRotationMatrix::MakeFromX(LastAttackDir).Rotator();
        InputRotation.Pitch = 0;
        HyCharacterOwner->SetActorRotation(InputRotation);
    }
}

void UHyAction_LargeHit::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}

void UHyAction_LargeHit::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);
}

void UHyAction_LargeHit::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
}

FName UHyAction_LargeHit::GetMontageSectionName_Implementation()
{
    if (animMontage)
    {
        const FName SectionName = animMontage->GetSectionName(SectionIndex);

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
