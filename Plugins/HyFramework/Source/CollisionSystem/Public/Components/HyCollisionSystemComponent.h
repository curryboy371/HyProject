// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HyActorComponent.h"

#include "CollisionTypes.h"

#include "GameplayTagContainer.h"
#include "HyCollisionSystemComponent.generated.h"


#define MAX_ATTACKABLE_COUNT 100
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLLISIONSYSTEM_API UHyCollisionSystemComponent : public UHyActorComponent
{
	GENERATED_BODY()
	
public:
	UHyCollisionSystemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UHyActorComponent을(를) 통해 상속됨
	virtual void InitializeHyActorComponent() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Hy | Collision")
	void SetEquipWeapon(const FGameplayTag& InEquipTag, const bool bCombatMode);

public:

	// 공격 충돌 활성화 및 비활성화 함수
	void EnableAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet);
	void DisableAttackCollider();

protected:
	void ColliderTraceSetup();
	void UpdateTraceSweep();

	bool SweepSingle(const FTraceData& InTraceData, const FCollisionQueryParams& InCollisionParams, const bool bIsLerpSweep, FHitResult& OutHitResult);
	bool SweepMulti(const FTraceData& InTraceData, const FCollisionQueryParams& InCollisionParams, const bool bIsLerpSweep, TArray<FHitResult>& OutHitResults);

	bool TakeDamage(const FGameplayTag& InAttackCollisionTag, const FGameplayTag& InHitTag, const FHitResult& InHitResult);

	void ApplyAttackImpact(FHitResult& HitResult, const FAttackCollisionSettings& InAttackCollisionSettings);

	void ResetIgnoreActors();

protected:
	void DebugDrawCharacterCapsule();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inven")
	TObjectPtr<class UHyInventorySystemComponent> InventorySystemComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	TArray<FColliderTraceInfo> AttackColliderTraces;

	UPROPERTY(BlueprintReadOnly, Category = "Collision")
	TArray<FColliderTraceInfo> AttackColliderTraceInsts;


	FAttackCollisionSettings CurAttackCollisionSet; // 현재 공격에 대한 충돌 정보
	TSet<FGameplayTag> AttackCompletionTags; // 공격이 완료된 collider tag


	FCollisionQueryParams CollisionMainParams; // 충돌 제외할 ignore actor list 관리하는 구조체 - 지속적인 Tick 충돌에서 사용
	FCollisionQueryParams CollisionSubParams; // 충돌 제외할 ignore actor list 관리하는 구조체 - 일시적인 Anim Noti 충돌에서 사용


	bool bOnAttack = false; // 현재 공격중인지 여부
	bool bSucessHit = false; // 공격이 성공적으로 적에게 맞았는지 여부


protected:
	FGameplayTag CurEquipWeaponTag;

};
