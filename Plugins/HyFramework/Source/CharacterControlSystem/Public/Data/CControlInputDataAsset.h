// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "CControlTypes.h"

#include "CControlInputDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERCONTROLSYSTEM_API UCControlInputDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UCControlInputDataAsset()
	{
		KeyInput = EKeyInput::IA_None;
		InputAction = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	EKeyInput KeyInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputAction> InputAction;
};
