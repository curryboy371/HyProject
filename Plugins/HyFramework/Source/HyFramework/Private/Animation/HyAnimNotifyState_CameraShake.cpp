// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotifyState_CameraShake.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"
#include "Actors/Character/HyMyPlayerBase.h"

#include "HyTypes.h"

#include "HyCoreMacro.h"

void UHyAnimNotifyState_CameraShake::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);



}

void UHyAnimNotifyState_CameraShake::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyEnd(MeshComp, Animation, EventReference);
}

void UHyAnimNotifyState_CameraShake::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);


}
