// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "GameplayTagContainer.h"


#include "BTDecorator_CompareAction.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTDecorator_CompareAction : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_CompareAction();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	TArray<FGameplayTag> CheckActionTags;

};
