// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "ActionsTypes.h"
#include "GameplayTagContainer.h"

#include "BTTaskNode_ExcuteAction.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTTaskNode_ExcuteAction : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_ExcuteAction();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action)
	FGameplayTag ActionTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action)
	EActionPriority ActionPriority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action)
	FString ActionContext;


};
