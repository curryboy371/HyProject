// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyBaseAnimNotifyState.h"

void UHyBaseAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);


}

void UHyBaseAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyEnd(MeshComp, Animation, EventReference);


}

void UHyBaseAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

const bool UHyBaseAnimNotifyState::IsGameWorld(USkeletalMeshComponent* MeshComp)
{
    if (!MeshComp || !MeshComp->GetWorld())
    {
        return MeshComp->GetWorld()->IsGameWorld();
    }

    return false;
}
