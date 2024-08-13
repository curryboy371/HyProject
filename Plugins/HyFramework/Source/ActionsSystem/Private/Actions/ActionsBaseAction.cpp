// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionsBaseAction.h"

#include "GameFramework/Character.h"


#include "Components/ActionsSystemComponent.h"
#include "Animation/AnimInstance.h"

#include "Animation/AnimMontage.h"


#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>

#include "HyCoreLogging.h"


UActionsBaseAction::UActionsBaseAction()
{
    ActionSystemCom = nullptr;


    CharacterOwner = nullptr;
    animMontage = nullptr;

    ActionTag = FGameplayTag::EmptyTag;
    
}

void UActionsBaseAction::ExecuteAction()
{


    if (animMontage && ActionSystemCom)
    {
        if (bBindMontageEvent)
        {
            BindMontageEvents();
        }

        PrepareMontageInfo(); // Action에 있는 몽타주 정보를 MontageInfo에 Set
        ActionSystemCom->PlayMontage(MontageInfo, StartFrame);
        bIsExecutingAction = true;
    }
    else
    {
        ExitAction();
    }
}

void UActionsBaseAction::ExitAction()
{
    if (ActionSystemCom)
    {
        if (ActionSystemCom->IsEmptyStoredAction())
        {
            ActionSystemCom->SetDefaultStoredActionTag();
        }

        ActionSystemCom->InternalExitAction();
    }
}

void UActionsBaseAction::Internal_OnActivated(TObjectPtr<UActionsSystemComponent> InActionSystemCom, TObjectPtr<UAnimMontage> InAnimMontage, const FString& InContext)
{
    ActionSystemCom = InActionSystemCom;
    animMontage = InAnimMontage;
    if (ActionSystemCom)
    {
        CharacterOwner = ActionSystemCom->GetCharacterOwner();
        ActionTag = ActionSystemCom->GetPerformingActionTag();
    }

    // Pre AnimationSet
    OnActionStarted(InContext);

    // Action에 설정된 몽타주를 실행
    if (ActionConfig.bAutoExecute)
    {
        ExecuteAction();
    }

    // Completed AnimationSet
    OnActionSetupCompleted(InContext);
}

void UActionsBaseAction::Internal_OnDeactivated()
{
    if (bIsExecutingAction)
    {
        bIsExecutingAction = false;
    }

    OnActionEnded();
}

void UActionsBaseAction::PrepareMontageInfo()
{
    MontageInfo.ActionMontage = animMontage;
    MontageInfo.MontageBlend = ActionConfig.MontageBlend;
    MontageInfo.ReproductionSpeed = GetPlayRate();
    MontageInfo.StartSectionName = GetMontageSectionName();

}

void UActionsBaseAction::BindMontageEvents()
{
    if (CharacterOwner)
    {
        UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance());
        if (animinst)
        {
            animinst->OnMontageStarted.AddDynamic(this, &UActionsBaseAction::HandleMontageStarted);
        }
    }
}

void UActionsBaseAction::UnbindMontageEvents()
{
    if (CharacterOwner)
    {
        UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance());

        if (animinst)
        {
            animinst->OnMontageStarted.RemoveDynamic(this, &UActionsBaseAction::HandleMontageStarted);
            animinst->OnMontageEnded.RemoveDynamic(this, &UActionsBaseAction::HandleMontageFinished);
        }
    }
}

bool UActionsBaseAction::GetMontageRate(float& OutMontageRate)
{
    if (CharacterOwner && CharacterOwner->GetMesh())
    {
        UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance());
        if (animinst)
        {
            if (MontageInfo.ActionMontage)
            {
                OutMontageRate = animinst->Montage_GetPlayRate(MontageInfo.ActionMontage);
                return true;
            }
        }
    }

    return false;
}

bool UActionsBaseAction::GetMontageProgress(float& OutPregress)
{
    // 하나의 몽타주 섹션에서만 사용되도록 변경 ( 임시 ) 
    // 몽타주는 섹션 순서대로 진행된다는 가정하에 사용
    // 재생중인 몽타주 비율 반환
    if (MontageInfo.ActionMontage && CharacterOwner)
    {
        if (UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance()))
        {
            // 현재까지 진행된 섹션의 길이
            //float MontageLength = 0.0f;
            //int32 CurSectionIdx = MontageInfo.ActionMontage->GetSectionIndex(GetMontageSectionName());
            //CurSectionIdx = FMath::Clamp(CurSectionIdx, 0, CurSectionIdx);
            //
            //for (int32 i = 0; i <= CurSectionIdx; ++i)
            //{
            //    MontageLength += MontageInfo.ActionMontage->GetSectionLength(CurSectionIdx);
            //}
            if (animinst->Montage_IsPlaying(MontageInfo.ActionMontage))
            {
                float CurrentTime = animinst->Montage_GetPosition(MontageInfo.ActionMontage);
                OutPregress = CurrentTime;
                return true;
            }

            //LOG_V("CurrentTime %f  MontageLength %f", CurrentTime, MontageLength);
            //
            //if (MontageLength > 0.f)
            //{
            //    OutPregress = CurrentTime / MontageLength;
            //    return true;
            //}
        }
    }
    return false;
}

int32 UActionsBaseAction::GetCurMontageSectionIdx()
{
    int32 CurSectionIndex = 0;
    if (MontageInfo.ActionMontage && CharacterOwner)
    {
        CurSectionIndex = MontageInfo.ActionMontage->GetSectionIndex(GetMontageSectionName());
        CurSectionIndex = FMath::Clamp(CurSectionIndex, 0, CurSectionIndex);
    }


    return CurSectionIndex;
}

int32 UActionsBaseAction::GetCurMontageSectionLength()
{
    int32 MaxSectionIndex = 0;
    if (MontageInfo.ActionMontage && CharacterOwner)
    {
        MaxSectionIndex = MontageInfo.ActionMontage->CompositeSections.Num();
    }

    return MaxSectionIndex;

}

void UActionsBaseAction::HandleMontageFinished(class UAnimMontage* InAnimMontage, bool InbInterruptted)
{
    if (animMontage == InAnimMontage && bIsExecutingAction && !InbInterruptted)
    {
        ExitAction();
    }
}

void UActionsBaseAction::HandleMontageStarted(class UAnimMontage* InAnimMontage)
{
    UAnimInstance* animinst = (CharacterOwner->GetMesh()->GetAnimInstance());

    UnbindMontageEvents();

    if (animinst)
    {
        // Bind
        if (animMontage == InAnimMontage)
        {
            animinst->OnMontageEnded.AddDynamic(this, &UActionsBaseAction::HandleMontageFinished);
        }
    }
}

void UActionsBaseAction::PlayEffects_Implementation()
{
    //UNPGameInstance* NPGameInstance = Cast<UNPGameInstance>(GWorld->GetGameInstance());
    //if (NPGameInstance)
    //{
    //    if (TObjectPtr<UNPFXDispatcher> FXDispatcher = NPGameInstance->GetFXDispatcher())
    //    {
    //        FXDispatcher->PlayActionFX(ActionConfig.ActionEffect, CharacterOwner);
    //    }
    //}
}


