// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "ActionsTypes.h"


#include "BTDecorator_CheckActionType.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTDecorator_CheckActionType : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_CheckActionType();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	EActionType ActionType;
};
