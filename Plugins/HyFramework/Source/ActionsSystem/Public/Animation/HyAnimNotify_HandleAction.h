// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HyBaseAnimNotify.h"

#include "ActionsTypes.h"

#include "HyAnimNotify_HandleAction.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONSSYSTEM_API UHyAnimNotify_HandleAction : public UHyBaseAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actions)
	EActionHandleType HandleType = EActionHandleType::EActionHandle_ConditionalStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actions)
	float BlendOut = 0.5f;

};
