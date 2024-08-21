// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotify_HandleAction.h"

#include "Interface/ActionsCharacterInterface.h"
#include "HyCoreMacro.h"


void UHyAnimNotify_HandleAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!IsGameWorld(MeshComp))
	{
		return;
	}

	Super::Notify(MeshComp, Animation, EventReference);

	if (IActionsCharacterInterface* ActionsInterface = Cast<IActionsCharacterInterface>(MeshComp->GetOwner()))
	{
		ActionsInterface->HandleAction(HandleType, BlendOut);
	}
	else
	{
		ERR_V("Owner of MeshComp Owner is not IActionsCharacterInterface!");
	}

}
