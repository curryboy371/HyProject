// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HyCoreTypes.h"

#include "HyCoreDeveloperSettings.generated.h"

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
	};

	static const UHyCoreDeveloperSettings* GetDeveloperSetting();
	static UHyCoreDeveloperSettings* GetDeveloperSettingRef();
	
	const bool IsLogCategoryEnabled(FString InLogCategory) const
	{
		return true;
	}


public:
	const bool IsDebugDraw() const { return bDebugDraw; }
	const bool IsDebugWidget() const { return bDebugWidget; }

protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "HYCORE | DEBUG | DRAW")
	bool bDebugDraw;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "HYCORE | DEBUG | DRAW")
	bool bDebugWidget;



	// 빠른 로그 카테고리 설정
	UPROPERTY(config, EditAnywhere, Category = "HYCORE | DEBUG | LOG")
	ELogPrintType LogPrintType;

protected:
};
