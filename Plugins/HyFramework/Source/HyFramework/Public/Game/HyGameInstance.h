// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CControlTypes.h"

#include "HyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
public:
	virtual void Init();

	

public:
	FInputDataSet& GetInputDataSet() { return InputDataSet; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Input")
	FInputDataSet InputDataSet;

};
