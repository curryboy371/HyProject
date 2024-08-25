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

    UHyGameInstance* GameInstance = Cast<UHyGameInstance>(MeshComp->GetWorld()->GetGameInstance());
    if (!GameInstance)
    {
        ERR_V("GameInstance is nullptr");
        return;
    }

    UHySpawnManager* HySpawnManager = GameInstance->GetManager<UHySpawnManager>();
    if (!HySpawnManager)
    {
        ERR_V("HySpawnManager is nullptr");
        return;
    }

    AHyMyPlayerBase* Player = Cast<AHyMyPlayerBase>(MeshComp->GetOwner());
    if (!Player)
    {
        ERR_V("Player is nullptr");
        return;
    }

    if (Player->IsLocalPlayer())
    {
        MyPlayer = Player;
        bStartNotiState = true;

        OriginZoomLength = MyPlayer->GetCameraArmLength();
        TargetZoom = OriginZoomLength * TargetZoomRatio;
        MyPlayer->SetCameraZoomLock(true);
    }

}

void UHyAnimNotifyState_CameraZoom::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    if (!IsStartNotiState())
    {
        return;
    }

    if (!MyPlayer)
    {
        ERR_V("MyPlayer is nullptr");
		return;
    }

    MyPlayer->SetCameraZoomLock(false);
    MyPlayer->SetCameraArmLenth(OriginZoomLength);

    Super::NotifyEnd(MeshComp, Animation, EventReference);

}

void UHyAnimNotifyState_CameraZoom::NotifyInRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    if (!IsStartNotiState())
    {
        return;
    }

    if (!MyPlayer)
    {
        ERR_V("MyPlayer is nullptr");
        return;
    }

    CurZoomLength = FMath::Lerp(OriginZoomLength, TargetZoom, InOutAlphaRatio);

    MyPlayer->SetCameraArmLenth(CurZoomLength, true);

}

void UHyAnimNotifyState_CameraZoom::NotifyOutRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    if (!IsStartNotiState())
    {
        return;
    }

    if (!MyPlayer)
    {
        ERR_V("MyPlayer is nullptr");
        return;
    }

    CurZoomLength = FMath::Lerp(TargetZoom, OriginZoomLength, InOutAlphaRatio);
    MyPlayer->SetCameraArmLenth(CurZoomLength, true);

}
