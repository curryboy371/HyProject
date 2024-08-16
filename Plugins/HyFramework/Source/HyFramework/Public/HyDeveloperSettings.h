// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HyDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class HYFRAMEWORK_API UHyDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	static const UHyDeveloperSettings* GetDeveloperSetting();
	static UHyDeveloperSettings* GetDeveloperSettingRef();
	
public:

protected:

	
};
