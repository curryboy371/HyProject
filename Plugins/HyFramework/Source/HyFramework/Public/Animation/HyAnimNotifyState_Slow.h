// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyAnimNotifyState_InOutRatio.h"


#include "HyAnimNotifyState_Slow.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAnimNotifyState_Slow : public UHyAnimNotifyState_InOutRatio
{
	GENERATED_BODY()
public:
	UHyAnimNotifyState_Slow();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyInRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyOutRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);

protected:
	UPROPERTY(EditAnywhere, Category = Hy, meta = (ClampMin = 0.01f, UIMax = 1.f))
	float TargetTimeDilation = 0.5f; // 목표하는 타임 딜레이 값

private:
	float OriginalTimeDilation;
};
