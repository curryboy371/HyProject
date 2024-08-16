// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API AHyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AHyGameMode();


public:
	UFUNCTION(Exec)
	void SetLogDebugWidgetVisibility(bool bVisiblity);

private:
};
