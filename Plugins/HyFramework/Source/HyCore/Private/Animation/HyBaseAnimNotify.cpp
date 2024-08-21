// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyBaseAnimNotify.h"

void UHyBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if(!IsGameWorld(MeshComp))
	{
		return;
	}

	Super::Notify(MeshComp, Animation, EventReference);

}

const bool UHyBaseAnimNotify::IsGameWorld(USkeletalMeshComponent* MeshComp)
{
    if (MeshComp && MeshComp->GetWorld())
    {
        return MeshComp->GetWorld()->IsGameWorld();
    }

    return false;
}
