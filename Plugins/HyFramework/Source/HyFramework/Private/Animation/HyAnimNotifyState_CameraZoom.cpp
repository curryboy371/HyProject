// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotifyState_CameraZoom.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"
#include "Actors/Character/HyMyPlayerBase.h"

#include "HyTypes.h"

#include "HyCoreMacro.h"

void UHyAnimNotifyState_CameraZoom::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);



}

void UHyAnimNotifyState_CameraZoom::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyEnd(MeshComp, Animation, EventReference);
}

void UHyAnimNotifyState_CameraZoom::NotifyInRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
}

void UHyAnimNotifyState_CameraZoom::NotifyOutRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
}
