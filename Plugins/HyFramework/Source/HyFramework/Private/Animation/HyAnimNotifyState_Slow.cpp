// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotifyState_Slow.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"
#include "Actors/Character/HyMyPlayerBase.h"

#include "HyTypes.h"
#include "HyCoreMacro.h"

#include "Kismet/GameplayStatics.h"


UHyAnimNotifyState_Slow::UHyAnimNotifyState_Slow()
{
    TargetTimeDilation = 0.5f;
    OriginalTimeDilation = 1.0f;
}

void UHyAnimNotifyState_Slow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (AWorldSettings* WorldSettings = MeshComp->GetWorld()->GetWorldSettings())
    {
        OriginalTimeDilation = WorldSettings->TimeDilation;
    }
}

void UHyAnimNotifyState_Slow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    Super::NotifyEnd(MeshComp, Animation, EventReference);

    if (!IsStartNotiState())
    {
        return;
    }
}

void UHyAnimNotifyState_Slow::NotifyInRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    float NewTimeDilation = FMath::Lerp(OriginalTimeDilation, TargetTimeDilation, InOutAlphaRatio);
    UGameplayStatics::SetGlobalTimeDilation(MeshComp->GetWorld(), NewTimeDilation);
}

void UHyAnimNotifyState_Slow::NotifyOutRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    float NewTimeDilation = FMath::Lerp(OriginalTimeDilation, TargetTimeDilation, InOutAlphaRatio);
    UGameplayStatics::SetGlobalTimeDilation(MeshComp->GetWorld(), NewTimeDilation);
}
