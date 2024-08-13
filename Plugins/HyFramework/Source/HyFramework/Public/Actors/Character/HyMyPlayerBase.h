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

	AHyMyPlayerBase();

	virtual void CharacterDefaultSetup();
	virtual void ComponenetSetup();

	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// ICControlInputInterface을(를) 통해 상속됨
	void InputSetup() override;

	void InputFunctionMapping() override;

	void InputActionDataSetup(struct FInputDataSet* InInputDataSet) override;

	void InputActionMapping(class UEnhancedInputComponent* EnhancedInputComponent) override;



public:


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

};
