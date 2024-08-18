// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CControlTypes.h"

#include "HyCharacterMovementComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocomotionStateChanged, ELocomotionState, InState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveStanceChanged, EMovementStance, InStance);

/**
 * 
 */
UCLASS()
class CHARACTERCONTROLSYSTEM_API UHyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UHyCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void SetOwnerReference();
public:
	void UpdateLocomotion();

	void CalcGroundDistance();

	void SetLocomotionState(ELocomotionState InState);


	void HandleStateChanged(ELocomotionState InChangeState);
public:
	FORCEINLINE float GetGroundDistance() const { return GroundDistance; }
	FORCEINLINE void SetGroundDistance(float InGroundDistance) { GroundDistance = InGroundDistance; }


	UFUNCTION(BlueprintPure, Category = "CControl | Movement")
	FORCEINLINE ELocomotionState GetCurLocomotionState() const { return CurLocomotionState; }

	UFUNCTION(BlueprintPure, Category = "CControl | Movement")
	FORCEINLINE ELocomotionState GetTargetLocomotionState() const { return TargetLocomotionState.State; }

protected:
	UPROPERTY()
	TObjectPtr<class UHyAnimInstance> AnimInstance;


protected:
	UPROPERTY(BlueprintAssignable)
	FOnLocomotionStateChanged OnLocomotionStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnLocomotionStateChanged OnTargetLocomotionStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnMoveStanceChanged OnMovementStanceChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CControl | Movement")
	TArray<FLocomotionState> LocomotionStates;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CControl | Movement")
	TArray<FMovStances> MovementStances;

	UPROPERTY()
	FLocomotionState TargetLocomotionState;

	UPROPERTY()
	ELocomotionState CurLocomotionState;

	UPROPERTY()
	EMovementStance CurMovestance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CControl | Movement")
	ELocomotionState DefaultState = ELocomotionState::EJog;

	// Sprint 가능 각도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CControl | Movement")
	float SprintDirectionCone = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "CControl | Movement")
	float GroundTraceDistance = 3000.f;

	float GroundDistance;
};
