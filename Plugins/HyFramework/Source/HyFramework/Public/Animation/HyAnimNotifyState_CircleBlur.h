// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyAnimNotifyState_InOutRatio.h"
#include "HyAnimNotifyState_CircleBlur.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyAnimNotifyState_CircleBlur : public UHyAnimNotifyState_InOutRatio
{
	GENERATED_BODY()
	
public:
	UHyAnimNotifyState_CircleBlur();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


	virtual void NotifyInRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyOutRatio(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);


protected:
	UPROPERTY(EditAnywhere, Category = Hy, meta = (ClampMin = 0.f, UIMax = 1.f))
	float Weight;


private:
	float CurWeight;

};
