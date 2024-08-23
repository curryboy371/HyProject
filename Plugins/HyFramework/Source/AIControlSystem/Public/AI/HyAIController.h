// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include <BehaviorTree/Blackboard/BlackboardKey.h>


#include "HyAIController.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API AHyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AHyAIController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	void BlackBoardKeyBindings();
	void BlackBoardKeyInit();


protected:
	TObjectPtr<class IActionsCharacterInterface> OwnerActionsInterface;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UBlackboardComponent> BlackboardComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hy")
	TObjectPtr<class UBehaviorTree> BehaviorTree;


protected:
	struct FBlackboard::FKey
		targetActorKey,
		targetActorDistanceKey,
		targetPointLocationKey,
		targetDistanceKey,
		isPausedKey,
		homeDistanceKey;

	FVector HomeLocation;

};
