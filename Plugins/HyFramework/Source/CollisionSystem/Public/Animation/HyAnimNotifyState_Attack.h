// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyBaseAnimNotifyState.h"


#include "CollisionTypes.h"

#include "HyAnimNotifyState_Attack.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONSYSTEM_API UHyAnimNotifyState_Attack : public UHyBaseAnimNotifyState
{
	GENERATED_BODY()
public:
	UHyAnimNotifyState_Attack();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, Category = Hy)
	FAttackCollisionSettings AttackCollisionSet;


};
