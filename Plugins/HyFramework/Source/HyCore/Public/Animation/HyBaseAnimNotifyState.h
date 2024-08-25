// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HyBaseAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class HYCORE_API UHyBaseAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UHyBaseAnimNotifyState();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;


protected:
	const bool IsGameWorld(USkeletalMeshComponent* MeshComp);
	const bool IsStartNotiState() { return bStartNotiState; }


protected:
	bool  bStartNotiState;
	float StartTime;
	float EndTime;
	float TotalDurationTime;
	float DeltaTime;
	float RemainAlphaRatio;
};
