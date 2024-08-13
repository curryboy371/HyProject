// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CControlTypes.h"

#include "GameplayTagContainer.h"

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
	const bool GetInputDataSet(const FGameplayTag& InInputTag, FInputDataSet& OutInputData);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Input")
	TArray<FInputDataSet> InputDataSet;

};
