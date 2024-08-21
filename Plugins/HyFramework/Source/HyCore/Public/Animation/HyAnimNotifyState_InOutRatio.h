// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyBaseAnimNotifyState.h"
#include "HyAnimNotifyState_InOutRatio.generated.h"

/**
 * 
 */
UCLASS()
class HYCORE_API UHyAnimNotifyState_InOutRatio : public UHyBaseAnimNotifyState
{
	GENERATED_BODY()
public:
	UHyAnimNotifyState_InOutRatio();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;


	virtual void NotifyInRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) {};
	virtual void NotifyOutRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) {};

protected:
	UPROPERTY(EditAnywhere, Category = Hy, meta = (ClampMin = 0.011f, UIMax = 1.f))
	float InRatio; // In 비율

	UPROPERTY(EditAnywhere, Category = Hy, meta = (ClampMin = 0.01f, UIMax = 1.f))
	float OutRatio; // Out 비율

	float TargetValue = 0.0f;

	float InOutAlphaRatio;

	float InDuration;
	float OutDuration;
	float OutStartTime;
};


