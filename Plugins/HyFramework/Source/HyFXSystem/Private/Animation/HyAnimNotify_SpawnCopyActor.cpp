// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotify_SpawnCopyActor.h"
#include "Actors/HyCopyActor.h"
#include "HyCoreMacro.h"


void UHyAnimNotify_SpawnCopyActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (IsGameWorld(MeshComp) == false)
	{
		return;
	}

	if (!CopyActor)
	{
		ERR_V("CopyActor is nullptr");
		return;
	}

	Super::Notify(MeshComp, Animation, EventReference);

	if (AHyCopyActor* HyCopyActor = MeshComp->GetWorld()->SpawnActor<AHyCopyActor>(CopyActor, MeshComp->GetComponentToWorld()))
	{
		HyCopyActor->SetCopyActor(MeshComp);
		HyCopyActor->SetDuration();
	}

}
