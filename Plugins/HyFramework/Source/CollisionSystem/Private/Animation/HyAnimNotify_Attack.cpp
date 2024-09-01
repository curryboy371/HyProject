// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotify_Attack.h"
#include "Interface/CollisionCharacterInterface.h"

#include "HyCoreMacro.h"


UHyAnimNotify_Attack::UHyAnimNotify_Attack()
{
	AttackCollisionSet.ResetNotify();
}

void UHyAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!IsGameWorld(MeshComp))
	{
		return;
	}

	Super::Notify(MeshComp, Animation, EventReference);
	if (ICollisionCharacterInterface* CollisionInterface = Cast<ICollisionCharacterInterface>(MeshComp->GetOwner()))
	{
		CollisionInterface->NotifyAttackCollider(AttackCollisionSet);
	}
	else
	{
		ERR_V("CollisionInterface is nullptr");
	}
}
