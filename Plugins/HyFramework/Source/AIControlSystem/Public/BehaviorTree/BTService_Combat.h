// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Combat.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UBTService_Combat : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	void UpdateCombatService(UBehaviorTreeComponent& OwnerComp);

protected:
	UPROPERTY(BlueprintReadOnly, Category = AI)
	TObjectPtr<class AHyAIController> HyAIController;

	UPROPERTY(BlueprintReadOnly, Category = AI)
	TObjectPtr < class AActor> TargetActor;

	UPROPERTY(BlueprintReadOnly, Category = AI)
	TObjectPtr<class AHyCharacterBase> CharacterOwner;



protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AI)
	float ForceMoveCheckTime = 0.2f;

	float SpendTime = 0.f;


	FVector LastTargetLocation;
};
