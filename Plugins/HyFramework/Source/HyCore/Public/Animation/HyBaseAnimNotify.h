// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HyBaseAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class HYCORE_API UHyBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


	const bool IsGameWorld(USkeletalMeshComponent* MeshComp);
};
