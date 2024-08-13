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
	

	UFUNCTION(BlueprintCallable, Category = "Hy | Property")
	UHyAnimInstance* GetOwningAnimInstance() const;
	
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
	UPROPERTY(BlueprintReadOnly, Category = "Hy | CControl | CharacterData")
	FCharacterStateData CharacterStateData;

};
