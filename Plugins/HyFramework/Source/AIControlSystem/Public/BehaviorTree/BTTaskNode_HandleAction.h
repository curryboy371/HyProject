// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ActionsTypes.h"
#include "BTTaskNode_HandleAction.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTTaskNode_HandleAction : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_HandleAction();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	EActionHandleType ActionType = EActionHandleType::EActionHandle_ConditionalStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float BlendOut = 0.5f;

};
