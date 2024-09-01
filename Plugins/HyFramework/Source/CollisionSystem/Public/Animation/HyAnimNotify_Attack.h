// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyBaseAnimNotify.h"
#include "CollisionTypes.h"


#include "HyAnimNotify_Attack.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONSYSTEM_API UHyAnimNotify_Attack : public UHyBaseAnimNotify
{
	GENERATED_BODY()
	
public:
	UHyAnimNotify_Attack();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, Category = Hy)
	FAttackCollisionSettings AttackCollisionSet;
};
