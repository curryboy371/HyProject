// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControlTypes.h"

#include "CollisionTypes.h"

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




	UFUNCTION(BlueprintCallable, Category = "Hy | Target")
	void HandleOwnerCharacterDamaged(const FHyDamageEvent& InDamageEvent, const FGuid& InDealerGuid);


public:
	UFUNCTION(BlueprintCallable, Category = "Hy | Target")
	void SetTarget(AActor* InTarget);

	AActor* GetTargetActorBBK() const;
	const FVector GetTargetLocationBBK() const;
	const float GetHomeDistanceBBK() const;

	EAIState GetAIStateBBK() const;



	void SetAIStateBBK(EAIState InaiState);
	void SetTargetActorBBK(AActor* InTarget);
	void SetTargetLocationBBK(const FVector& InTargetLocation);
	void SetTargetDistanceBBK(float InDistance);
	void SetHomeDistanceBBK(float InDistance);


public:
	FORCEINLINE const FVector& GetHomeLocation() const {return HomeLocation; };

	FORCEINLINE float GetLoseTargetDistance() const { return LoseTargetDistance; }
	FORCEINLINE float GetHomeRange() const { return HomeRange; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = Hy)
	TObjectPtr<class AHyCharacterBase> CharacterOwner;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | Component")
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
		aiStateKey,
		homeDistanceKey;

	FVector HomeLocation;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Config")
	float LoseTargetDistance = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Config")
	float HomeRange = 500.f;
};
