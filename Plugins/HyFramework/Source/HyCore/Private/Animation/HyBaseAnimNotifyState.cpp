// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyBaseAnimNotifyState.h"

UHyBaseAnimNotifyState::UHyBaseAnimNotifyState()
{
    bStartNotiState = false;
    RemainAlphaRatio = DeltaTime = EndTime = StartTime = 0.0f;
}

void UHyBaseAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    StartTime = MeshComp->GetWorld()->GetTimeSeconds();
    EndTime = StartTime + TotalDuration;
    TotalDurationTime = TotalDuration;

    DeltaTime = 0.0f;
    RemainAlphaRatio = 0.0f;
}

void UHyBaseAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyEnd(MeshComp, Animation, EventReference);

    RemainAlphaRatio = DeltaTime = EndTime = StartTime = 0.0f;
    bStartNotiState = false;
}

void UHyBaseAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

    if (!bStartNotiState)
    {
        return;
    }

    RemainAlphaRatio = FMath::Clamp((MeshComp->GetWorld()->GetTimeSeconds() - StartTime) / (EndTime - StartTime), 0.0f, 1.0f);
    DeltaTime += FrameDeltaTime;
}

const bool UHyBaseAnimNotifyState::IsGameWorld(USkeletalMeshComponent* MeshComp)
{
    if (MeshComp && MeshComp->GetWorld())
    {
        return MeshComp->GetWorld()->IsGameWorld();
    }

    return false;
}
