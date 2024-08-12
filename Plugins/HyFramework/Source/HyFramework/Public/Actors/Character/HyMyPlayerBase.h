// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Character/HyPlayerBase.h"

#include "CControlTypes.h"

#include "HyMyPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API AHyMyPlayerBase : public AHyPlayerBase
{
	GENERATED_BODY()

	AHyMyPlayerBase();

	virtual void CharacterDefaultSetup();
	virtual void ComponenetSetup();

	void InputSetup();

	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


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
	TMap<EKeyInput, FInputActionData> InputDataMap;
};
