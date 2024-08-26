// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AIState.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTService_AIState : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_AIState();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
