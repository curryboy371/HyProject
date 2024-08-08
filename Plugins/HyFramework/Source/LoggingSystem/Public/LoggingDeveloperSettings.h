// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LoggingDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class LOGGINGSYSTEM_API ULoggingDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	ULoggingDeveloperSettings() {};

	static const ULoggingDeveloperSettings* GetDeveloperSetting();
	static ULoggingDeveloperSettings* GetDeveloperSettingRef();
	

public:
	const bool IsDebugDraw() const { return bDebugDraw; }

protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "DEBUG | DRAW")
	bool bDebugDraw;

};
