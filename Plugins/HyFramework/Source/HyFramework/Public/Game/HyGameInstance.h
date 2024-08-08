// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	
};
