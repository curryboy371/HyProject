// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HyActorComponent.h"
#include "HyFXTypes.h"

#include "HyFXSystemComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HYFXSYSTEM_API UHyFXSystemComponent : public UHyActorComponent
{
	GENERATED_BODY()
	
public:
	UHyFXSystemComponent();

	virtual void InitializeHyActorComponent() override;

protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = FX)
	void PlayAttachedFX(const FActionFX& InActionFX, class ACharacter* InInstigator);

	UFUNCTION(BlueprintCallable, Category = FX)
	void StopFXAttached(const FActionFX& InActionFX, class ACharacter* InInstigator);


protected:
	void SpawnAttachedFX(const FActionFX& InActionFX, class ACharacter* InInstigator);

};
