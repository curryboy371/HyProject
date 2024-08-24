// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotifyState_Attack.h"

#include "Interface/CollisionCharacterInterface.h"

#include "HyTagSubsystem.h"
#include "HyCoreMacro.h"

UHyAnimNotifyState_Attack::UHyAnimNotifyState_Attack()
{
	AttackCollisionSet.ResetState();
	AttackCollisionSet.TagName = UHyTagSubsystem::DefaultHitTag;
}

void UHyAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!IsGameWorld(MeshComp))
	{
		return;
	}


	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ICollisionCharacterInterface* CollisionInterface = Cast<ICollisionCharacterInterface>(MeshComp->GetOwner()))
	{
		CollisionInterface->EnableAttackCollider(AttackCollisionSet);
	}
	else
	{
		ERR_V("CollisionInterface is nullptr");
	}

}

void UHyAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!IsGameWorld(MeshComp))
	{
		return;
	}


	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ICollisionCharacterInterface* CollisionInterface = Cast<ICollisionCharacterInterface>(MeshComp->GetOwner()))
	{
		CollisionInterface->DisableAttackCollider();
	}
	else
	{
		ERR_V("CollisionInterface is nullptr");
	}

}

void UHyAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if (!IsGameWorld(MeshComp))
	{
		return;
	}

	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);


}
