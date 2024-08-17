// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionsSystemComponent.h"
#include "GameFramework/Character.h"

#include "HyCoreMacro.h"


// Sets default values for this component's properties
UActionsSystemComponent::UActionsSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CMActionsDataSet = UActionsDataAsset::StaticClass();

	ResetActionState();
	// ...
}


// Called when the game starts
void UActionsSystemComponent::BeginPlay()
{
	Super::BeginPlay();


    // EquipableActionInstMap을 생성
    EquipableActionsInstMap.Empty();
    for (const auto& ActionSetclass : EquipableActionSets)
    {
        if (ActionSetclass.ActionsSet)
        {
            UActionsDataAsset* EquipSet = NewObject<UActionsDataAsset>(this, ActionSetclass.ActionsSet);
            EquipableActionsInstMap.Add(ActionSetclass.TagName, EquipSet);
        }
        else
        {
            ERR_V("Invalid EquipableActions Class");
        }
    }
    
    if (CMActionsDataSet)
    {
        CMActionsDataInst = NewObject<UActionsDataAsset>(this, CMActionsDataSet);
    }
    else
    {
        ERR_V("Invalid CMActionsDataSet Class");
    }


    CharacterOwner = Cast<ACharacter>(GetOwner());
    if (CharacterOwner)
    {
        AnimInst = CharacterOwner->GetMesh()->GetAnimInstance();
        if (AnimInst == nullptr)
        {
            ERR_V("Invalid AnimInst");
        }
    }
    else
    {
        ERR_V("Invalid CharacterOwner");
    }

    ResetActionState();
}


// Called every frame
void UActionsSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsPerformingAction && PerformingAction)
    {
        PerformingAction->OnTick(DeltaTime);
    }
}

bool UActionsSystemComponent::TriggerAction(const FActionExcuteData& InActionExcuteData, bool bCanBeStored/* = false*/)
{
    // InActionTag 태그로 Action을 트리거하려고 시도하는 함수
    // Priority를 비교하여 Action이 실행될지, 무시될지, 
    // bCanBeStored가 true이고 진행중인 action이 있다면 다음 Action을 위해 저장될지 ( Priority도 비교)
    // contextString은 `OnActionStarted에서 받아 Flag 처럼 사용함

    bool bSuccessAction = false;
    if (InActionExcuteData == FGameplayTag::EmptyTag)
    {
        ERR_V("InActionTag is EmptyTag");
        return bSuccessAction;
    }

    OnActionTriggered.Broadcast(InActionExcuteData.TagName, InActionExcuteData.ActionPriority);

    FActionState ActionState;
    if (GetActionByTag(InActionExcuteData.TagName, ActionState) && ActionState.Action && CanExecuteAction(InActionExcuteData.TagName))
    {
        if (((InActionExcuteData.ActionPriority > CurActionExcuteData.ActionPriority)) || InActionExcuteData.ActionPriority == EActionPriority::EHighest)
        {
            // 현재 액션보다 우선순위가 크거나, 가장 높은 우선순위이면 액션 실행
    
            LaunchAction(InActionExcuteData);
            bSuccessAction = true;
        }
        else if (CurActionExcuteData != FGameplayTag::EmptyTag && bCanBeStored)
        {
            // 우선순위가 떨어지고, 저장 가능한 액션이라면 Store
            StoreAction(InActionExcuteData);
        }
    }
    else
    {
        ERR_V("Invalid Action");
    }

    return bSuccessAction;
}

void UActionsSystemComponent::LaunchAction(const FActionExcuteData& InActionExcuteData)
{
    FActionState ActionState;
    if (GetActionByTag(InActionExcuteData.TagName, ActionState) && ActionState.Action)
    {
        if (PerformingAction)
        {
            // 진행중인 액션이 있다면 
            // 새로운 액션은 Transit
            // 진행중이던 Action Terminate
            ActionState.Action->OnActionTransition(PerformingAction);
            TerminateCurrentAction();
        }
        OnActionStarted.Broadcast(InActionExcuteData.TagName);

        PerformingAction = ActionState.Action;
        bIsPerformingAction = true;
        PerformingAction->SetTerminated(false);

        // 한번에 초기화
        CurActionExcuteData = InActionExcuteData;

        PerformingAction->Internal_OnActivated(this, ActionState.ActionMontage, InActionExcuteData.ActionContext);


        if (PerformingAction && PerformingAction->GetActionConfig().bPlayEffectOnActionStart)
        {
            PerformingAction->PlayEffects();
        }
    }
}


void UActionsSystemComponent::StoreAction(const FActionExcuteData& InActionExcuteData)
{
    StoredActionExcuteData = InActionExcuteData;
}


void UActionsSystemComponent::FreeAction()
{
    if (StoredActionExcuteData == FGameplayTag::EmptyTag)
    {
        SetDefaultStoredActionTag();
    }

    bool bInclueTag = false;
    CurActionExcuteData.ResetData(bInclueTag);

    bool bRes = TriggerAction(StoredActionExcuteData, false);

    StoredActionExcuteData.ResetData();
}

void UActionsSystemComponent::PauseAction(bool bSetPause)
{
    if (CharacterOwner && CharacterOwner->GetMesh())
    {
        CharacterOwner->GetMesh()->bPauseAnims = bSetPause;
    }
}

void UActionsSystemComponent::ActionStart(const FGameplayTag& InActionTag, const FString& InContext)
{
    OnActionStarted.Broadcast(InActionTag);
    FActionState ActionState;

    if (GetActionByTag(InActionTag, ActionState) && ActionState.Action)
    {
        PerformingAction = ActionState.Action;
        ActionState.Action->SetCharacterOwner(CharacterOwner);
        ActionState.Action->OnActionStarted(InContext);
    }
}

void UActionsSystemComponent::ActionEnd(const FGameplayTag& InActionTag)
{
    FActionState ActionState;
    if (GetActionByTag(InActionTag, ActionState) && ActionState.Action)
    {
        ActionState.Action->OnActionEnded();
    }

}

void UActionsSystemComponent::ActionStopImmeditaley(float InBlendOutTime)
{
    if (StoredActionExcuteData == FGameplayTag::EmptyTag)
    {
        SetDefaultStoredActionTag();
    }

    FActionState ActionState;
    if (GetActionByTag(CurActionExcuteData.TagName, ActionState))
    {
        if (AnimInst)
        {
            AnimInst->Montage_Stop(InBlendOutTime, ActionState.ActionMontage);
        }
        else
        {
            ERR_V("AnimInst is null");
        }
    }

    bool bInclueTag = false;
    CurActionExcuteData.ResetData(bInclueTag);

    InternalExitAction();
}

void UActionsSystemComponent::PlayMontage(const FActionMontageInfo& InMontageInfo, float InStartFrame)
{
    MontageInfo = InMontageInfo;

    if (MontageInfo.ActionMontage && CharacterOwner)
    {
        SetMontageBlendType(MontageInfo);
        CharacterOwner->PlayAnimMontage(MontageInfo.ActionMontage, MontageInfo.ReproductionSpeed, MontageInfo.StartSectionName);
    }
}

void UActionsSystemComponent::InternalExitAction()
{
    if (bIsPerformingAction && PerformingAction)
    {
        // 현재 액션 종료
        TerminateCurrentAction();

        FGameplayTag EmptyActionTag = FGameplayTag::EmptyTag;
        if (StoredActionExcuteData != EmptyActionTag)
        {
            // NextAction
            bool bRes = TriggerAction(StoredActionExcuteData);
            StoredActionExcuteData.ResetData();
        }
        else
        {
            ERR_V("Next Acction Empty");
            // 비어있는 액션을 사용하지 않음.
        }

    }
}

void UActionsSystemComponent::TerminateCurrentAction()
{
    // 현재 진행중인 Action을 종료함
    if (bIsPerformingAction && PerformingAction && !PerformingAction->GetTerminated())
    {
        PerformingAction->Internal_OnDeactivated();
        PerformingAction->SetTerminated(true);
        PerformingAction = nullptr;
        OnActionFinished.Broadcast(CurActionExcuteData.TagName);
        CurActionExcuteData.ResetData();
    }
    bIsPerformingAction = false;
}

void UActionsSystemComponent::SetMontageBlendType(const FActionMontageInfo& InMontageInfo)
{
    if (InMontageInfo.ActionMontage)
    {
        switch (InMontageInfo.MontageBlend)
        {
        case EMontageBlendType::EMontageBlend_None: // 블렌드 인아웃 모두 안함
            InMontageInfo.ActionMontage->BlendIn.SetBlendTime(0.0f);
            InMontageInfo.ActionMontage->BlendOut.SetBlendTime(0.0f);
            break;

        case EMontageBlendType::EMontageBlend_Start: // 블렌드 아웃 안함
            InMontageInfo.ActionMontage->BlendOut.SetBlendTime(0.0f);
            break;

        case EMontageBlendType::EMontageBlend_End: // 블렌드 인 안함
            InMontageInfo.ActionMontage->BlendIn.SetBlendTime(0.0f);
            break;

        case EMontageBlendType::EMontageBlend_Both: // 블렌드 인 아웃 모두 함
            break;
        }

    }
}

void UActionsSystemComponent::SetPerformingActionPriority(EActionPriority InPriority)
{
    CurActionExcuteData.ActionPriority = InPriority;
}

void UActionsSystemComponent::SetStoredActionTag(const FActionExcuteData& InActionExcuteData, bool bForce/* = false*/)
{
    if (bForce || StoredActionExcuteData == FGameplayTag::EmptyTag || InActionExcuteData.ActionPriority > StoredActionExcuteData.ActionPriority)
    {
        StoreAction(InActionExcuteData);
    }
}

void UActionsSystemComponent::SetDefaultStoredActionTag(const bool bForce)
{
    SetStoredActionTag(DefaultActionExcuteData, bForce);
}

void UActionsSystemComponent::ClearPerformingActionState()
{
    if (PerformingAction)
    {
        PerformingAction->ClearActionState();
    }
}

TObjectPtr<class UActionsBaseAction> UActionsSystemComponent::GetCurrentAction(const FGameplayTag& InActionTag)
{
    FActionState ActionState;
    if (GetActionByTag(InActionTag, ActionState) && ActionState.Action)
    {
        return ActionState.Action;
    }

    return nullptr;
}

TObjectPtr<class UAnimMontage> UActionsSystemComponent::GetCurrentMontage(const FGameplayTag& InActionTag)
{
    FActionState ActionState;
    if (GetActionByTag(InActionTag, ActionState))
    {
        return ActionState.ActionMontage;
    }

    return nullptr;
}

bool UActionsSystemComponent::CanExecuteAction(const FGameplayTag& InActionTag) const
{
    FActionState ActionState;
    if (GetActionByTag(InActionTag, ActionState) && ActionState.Action)
    {
        return true;
    }
    else
    {
        ERR_V("Actions Conditions are not verified")
    }
    return false;
}

void UActionsSystemComponent::SetEquipActions(const FGameplayTag& InEquipTag)
{
    if (InEquipTag == FGameplayTag::EmptyTag)
    {
        ERR_V("InEquipTag is Empty");
        return;
    }

    CurEquipTag = InEquipTag;
}

bool UActionsSystemComponent::GetActionByTag(const FGameplayTag& InActionTag, FActionState& OutActionState) const
{
    // Action이 유효한지 Check한 후 OutActionState에 반환
    if (CMActionsDataInst)
    {
        if (GetEquipActionByTag(InActionTag, CurEquipTag, OutActionState))
        {
            // 1. 현재 EquipTag와 일치하는 EquipAction이 있는지 체크
            return true;
        }
        else if (GetCommonActionByTag(InActionTag, OutActionState))
        {
            // 2. 1이 없다면 공용 Action이 있는지 체크
            return true;
        }
    }
    else
    {
        return false;
    }
    return false;
}

bool UActionsSystemComponent::GetEquipActionByTag(const FGameplayTag& InActionTag, const FGameplayTag& InEquipTag, FActionState& OutActionState) const
{
    // EquipAction에서 tag로 action을 찾아 반환
    if (EquipableActionsInstMap.Contains(InEquipTag))
    {
        UActionsDataAsset* actionSet = EquipableActionsInstMap.FindChecked(InEquipTag);
        if (actionSet) 
        {
            return actionSet->GetActionByTag(InActionTag, OutActionState);
        }
    }
    return false;
}

bool UActionsSystemComponent::GetCommonActionByTag(const FGameplayTag& InActionTag, FActionState& OutActionState) const
{
    if (CMActionsDataInst)
    {
        return CMActionsDataInst->GetActionByTag(InActionTag, OutActionState);
    }
    return false;
}

const FGameplayTag UActionsSystemComponent::GetPerformingActionTag() const
{
    FGameplayTag PerformingTag = FGameplayTag::EmptyTag;

    if (bIsPerformingAction && PerformingAction)
    {
        PerformingTag = PerformingAction->GetActionTag();

    }

    return PerformingTag;
}

const bool UActionsSystemComponent::IsActionStopCondition() const
{
    // 현재 진행중인 Action을 조건에 따라 Stop or Continue
    if (PerformingAction)
    {
        return PerformingAction->IsStopConditional();
    }

    return false;
}

const bool UActionsSystemComponent::IsDefaultStoredAction() const
{
    //FGameplayTag DefaultTag = FNPTags::Get().GetDefaultAction(GetPerformingActionTag());
    //if (StoredAction == DefaultTag)
    {
        //return true;
    }
    return false;
}

const bool UActionsSystemComponent::IsLastMonstageSection() const
{
    // 현재 재생중인 몽타주가 마지막 섹션인지?
    if (bIsPerformingAction && PerformingAction)
    {
        if (PerformingAction->GetCurMontageSectionIdx() + 1 == PerformingAction->GetCurMontageSectionLength())
        {
            return true;
        }
    }
    return false;
}

void UActionsSystemComponent::ResetActionState()
{
    // reset value
    CurActionExcuteData.ResetData();
    StoredActionExcuteData.ResetData();
}

