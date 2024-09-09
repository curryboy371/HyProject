// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyBaseAnimNotify.h"
#include "HyAnimNotify_SpawnCopyActor.generated.h"

/**
 * 
 */
UCLASS()
class HYFXSYSTEM_API UHyAnimNotify_SpawnCopyActor : public UHyBaseAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHyCopyActor> CopyActor;
};
