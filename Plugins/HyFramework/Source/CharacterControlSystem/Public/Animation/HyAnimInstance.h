// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "GameplayTagContainer.h"

#include "CControlTypes.h"

#include "HyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERCONTROLSYSTEM_API UHyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UHyAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	

	bool IsEditorBlueprint();
	void SetCharacterReferences();

public:
	UFUNCTION(BlueprintCallable, Category = "Hy | CControl | Layer")
	void SetEquipLayer(const FGameplayTag& InEquipTag);

protected:
// Animaion Valus Update Functions 
	void UpdateLeaning(const float& DeltaSeconds);
	void UpdateLocation(const float& DeltaSeconds);
	void UpdateRotation(const float& DeltaSeconds);
	void UpdateVelocity(const float& DeltaSeconds);

	void UpdateAimData(const float& DeltaSeconds);
	void UpdateAcceleration(const float& DeltaSeconds);
	void UpdateStateData(const float& DeltaSeconds);
	void UpdateJump(const float& DeltaSeconds);


public:
	void SetCharacterStateData(const FCharacterStateData& InCharacterStateData) { CharacterStateData = InCharacterStateData; }
	void SetCharacterDefaultTagSet(const FCharacterDefaultTagSet& InCharacterDefaultTagSet) { CharacterDefaultTagSet = InCharacterDefaultTagSet; }


	const FAnimationVelocityData& GetVelocityData() const { return VelocityData; }
	const FAnimationLocationData& GetLocationData() const { return LocationData; }
	const FAnimationRotationData& GetRotationData() const { return RotationData; }
	const FAnimationJumpData& GetJumpData() const { return JumpData; }
	const FAnimationMovementData& GetMovementData() const { return MovementData; }
	const FAnimationAccelerationData& GetAccelerationData() const { return AccelerationData; }
	


	UFUNCTION(BlueprintPure, Category = "Hy | CControl | Movement")
	ELocomotionState GetCurLocomotionState() const;

	UFUNCTION(BlueprintPure, Category = "Hy | CControl | Movement")
	ELocomotionState GetTargetLocomotionState() const;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl")
	TObjectPtr<class ACharacter> CharacterOwner;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl")
	TObjectPtr<class UHyCharacterMovementComponent> CharacterMovementComp;

protected:
// Animation Values Update On Off
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Updates")
	FCControlUpdates AnimationUpdateSwitch;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | CControl | Layer")
	TArray<FHyAnimEquipLayerSet> EquipLayers;

	// Instances
	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | Layer")
	TObjectPtr<class UHyAnimEquipLayer> CurEquipLayerInst;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | AnimationData")
	FAnimationLocationData LocationData;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | AnimationData")
	FAnimationJumpData JumpData;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | AnimationData")
	FAnimationMovementData MovementData;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | AnimationData")
	FAnimationRotationData RotationData;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | AnimationData")
	FAnimationAccelerationData AccelerationData;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | AnimationData")
	FAnimationVelocityData VelocityData;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | CharacterData")
	FCharacterStateData CharacterStateData;

	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | CharacterData")
	FCharacterDefaultTagSet CharacterDefaultTagSet;
};
