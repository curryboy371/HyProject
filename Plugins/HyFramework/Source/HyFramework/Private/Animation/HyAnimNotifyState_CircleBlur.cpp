// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotifyState_CircleBlur.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"
#include "Actors/Character/HyMyPlayerBase.h"

#include "HyTypes.h"

#include "HyCoreMacro.h"


UHyAnimNotifyState_CircleBlur::UHyAnimNotifyState_CircleBlur()
{
	Weight = 1.f;
    CurWeight = 0.f;
}

void UHyAnimNotifyState_CircleBlur::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
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
    if(!HySpawnManager)
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
        bStartNotiState = true;
    }
}

void UHyAnimNotifyState_CircleBlur::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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
        Player->SetPPMValue(EPPMType::EPPM_Blur, 0.0f);
    }
    else
    {
        // 잘못된 상황, Blur를 끝내야함
        if (HySpawnManager->GetLocalPlayer())
        {
            HySpawnManager->GetLocalPlayer()->SetPPMValue(EPPMType::EPPM_Blur, 0.0f);

        }
    }

    CurWeight = 0.f;
    bStartNotiState = false;

}

void UHyAnimNotifyState_CircleBlur::NotifyInRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    if (!IsStartNotiState())
    {
        return;
    }

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
        CurWeight = FMath::Lerp(Weight, CurWeight, InOutAlphaRatio);
        Player->SetPPMValue(EPPMType::EPPM_Blur, CurWeight);
    }
    else
    {
        // 잘못된 상황, Blur를 끝내야함
        if (HySpawnManager->GetLocalPlayer())
        {
            HySpawnManager->GetLocalPlayer()->SetPPMValue(EPPMType::EPPM_Blur, 0.0f);
            bStartNotiState = false;
        }
    }

}

void UHyAnimNotifyState_CircleBlur::NotifyOutRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    if (!IsGameWorld(MeshComp))
    {
        return;
    }

    if (!IsStartNotiState())
    {
        return;
    }

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
        CurWeight = FMath::Lerp(Weight, CurWeight, InOutAlphaRatio);
        Player->SetPPMValue(EPPMType::EPPM_Blur, CurWeight);
    }
    else
    {
        // 잘못된 상황, Blur를 끝내야함
        if (HySpawnManager->GetLocalPlayer())
        {
            HySpawnManager->GetLocalPlayer()->SetPPMValue(EPPMType::EPPM_Blur, 0.0f);
            bStartNotiState = false;
        }
    }
}
