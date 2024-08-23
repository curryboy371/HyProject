// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HyCoreTypes.h"

#include "HyCoreDeveloperSettings.generated.h"

// Debug Draw 출력 옵션
UENUM(BlueprintType)
enum class EDebugDrawOption : uint8
{
	EDrawOption_None,
	EDrawOption_Select,
	EDrawOption_All,
};


UENUM(BlueprintType)
enum class EDebugDrawType : uint8
{
	EDrawType_None,
	EDrawType_Movement,
	EDrawType_Collision,
	EDrawType_Widget,
};

/**
 * 
 */

UCLASS(config = Game, defaultconfig)
class HYCORE_API UHyCoreDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UHyCoreDeveloperSettings() 
	{
		DebugDrawOption = EDebugDrawOption::EDrawOption_None;

	};

	static const UHyCoreDeveloperSettings* GetDeveloperSetting();
	static UHyCoreDeveloperSettings* GetDeveloperSettingRef();

public:
	const bool IsDrawEnable() const;

	const bool IsDebugDrawMovement() const ;
	const bool IsDebugDrawCollision() const;
	const bool IsDebugDrawWidget() const;

protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "HYCORE | DEBUG | DRAW")
	EDebugDrawOption DebugDrawOption;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "HYCORE | DEBUG | DRAW")
	TSet<EDebugDrawType> DebugDrawSelectTypes;

protected:
};
