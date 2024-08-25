// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimNotifyState_InOutRatio.h"

UHyAnimNotifyState_InOutRatio::UHyAnimNotifyState_InOutRatio()
{
	InRatio = 0.5f;
	OutRatio = 0.5f;

	TargetValue = 0.0f;

	InDuration = 0.0f;
	OutDuration = 0.0f;
	OutStartTime = 0.0f;
}

void UHyAnimNotifyState_InOutRatio::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!IsGameWorld(MeshComp))
	{
		return;
	}

	InOutAlphaRatio = OutStartTime = OutDuration = InDuration = TargetValue = 0.0f;

	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

}

void UHyAnimNotifyState_InOutRatio::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!IsGameWorld(MeshComp))
	{
		return;
	}

	if (!IsStartNotiState())
	{
		return;
	}


	Super::NotifyEnd(MeshComp, Animation, EventReference);

	InOutAlphaRatio = OutStartTime = OutDuration = InDuration = TargetValue = 0.0f;

}

void UHyAnimNotifyState_InOutRatio::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if (!IsGameWorld(MeshComp))
	{
		return;
	}

	if (!IsStartNotiState())
	{
		return;
	}

	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	InDuration = TotalDurationTime * InRatio;
	OutStartTime = TotalDurationTime * (1.0 - OutRatio);
	OutDuration = TotalDurationTime * OutRatio;

	if (DeltaTime <= InDuration)
	{
		// In Ratio 실행
		if (InDuration > 0.0f)
		{
			InOutAlphaRatio = DeltaTime / InDuration;
			NotifyInRatio(MeshComp, Animation, FrameDeltaTime, EventReference);
		}
	}
	else if (DeltaTime >= OutStartTime)
	{
		// Out Ratio 실행
		if(OutDuration > 0.0f)
		{
			InOutAlphaRatio = (DeltaTime - OutStartTime) / OutDuration;
			NotifyOutRatio(MeshComp, Animation, FrameDeltaTime, EventReference);
		}
	}

}
