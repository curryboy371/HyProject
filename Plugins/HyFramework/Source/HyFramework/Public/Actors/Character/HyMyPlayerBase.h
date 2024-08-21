// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Character/HyPlayerBase.h"

#include "CControlTypes.h"

#include "Interface/CControlInputInterface.h"
#include "HyMyPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API AHyMyPlayerBase : public AHyPlayerBase, public ICControlInputInterface
{
	GENERATED_BODY()

public:
	AHyMyPlayerBase();

protected:
	virtual void CharacterDefaultSetup();
	virtual void ComponenetSetup();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void LocalPlayerSetup();


	// PostProcessVolume
	void SetPostProcessVolume();
public:
	void SetPPMValue(EPPMType InPPMType, float InValue);

	void UpdateBlurWeight();

protected:
	// ICControlInputInterface을(를) 통해 상속됨
	void InputSetup() override;

	void InputFunctionMapping() override;

	void InputActionDataSetup(struct FInputDataSet* InInputDataSet) override;

	void InputActionMapping(class UEnhancedInputComponent* EnhancedInputComponent) override;



public:
	const bool IsLocalPlayer();

protected:
	TObjectPtr<class USpringArmComponent> GetCameraBoom() { return CameraBoomComp; }
	TObjectPtr<class UCameraComponent> GetFollowCamera() { return FollowCameraComp; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> CameraBoomComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> FollowCameraComp;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TArray<FInputActionData> InputDatas;

	// Input Function Map
	TMap<FName, void (AHyMyPlayerBase::*)(const FInputActionValue&)> InputFunctionMap;


	UPROPERTY()
	TMap<EPPMType, TObjectPtr<class UMaterialInstanceDynamic>> PPMMaterialMap;


protected:
	bool bSprintBlurOn;
};






