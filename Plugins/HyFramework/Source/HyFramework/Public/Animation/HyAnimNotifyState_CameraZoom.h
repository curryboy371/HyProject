// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyAnimNotifyState_InOutRatio.h"
#include "HyAnimNotifyState_CameraZoom.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAnimNotifyState_CameraZoom : public UHyAnimNotifyState_InOutRatio
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


	virtual void NotifyInRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyOutRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);

protected:
	UPROPERTY(EditAnywhere, Category = Hy, meta = (ClampMin = 100.f, UIMax = 1000.f))
	float TargetZoom = 100.0f; // 목표 Zoom Length


private:
	float OriginZoomLength = 0.0f;

};
