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
	UHyCoreDeveloperSettings() {};

	static const UHyCoreDeveloperSettings* GetDeveloperSetting();
	static UHyCoreDeveloperSettings* GetDeveloperSettingRef();
	
	const bool IsLogCategoryEnabled(FString InLogCategory) const
	{
		if (LogPrintType == ELogPrintType::ELOG_Hide)
		{
			return false;
		}
		else if (LogPrintType == ELogPrintType::ELOG_Output_ALL)
		{
			return true;
		}
		else
		{
			// 선택한 로그만 출력
			EHyModule HyModuleValue;
			if (EHyModuleHelper::FromString(InLogCategory, HyModuleValue))
			{
				return EnabledLogCategories.Contains(HyModuleValue);
			}

			return false;
		}
	}


public:
	const bool IsDebugDraw() const { return bDebugDraw; }

protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "HYCORE | DEBUG | DRAW")
	bool bDebugDraw;

	// 빠른 로그 카테고리 설정
	UPROPERTY(config, EditAnywhere, Category = "HYCORE | DEBUG | LOG")
	ELogPrintType LogPrintType;

	// 로그 카테고리를 활성화하기 위한 목록
	UPROPERTY(config, EditAnywhere, Category = "HYCORE | DEBUG | LOG")
	TSet<EHyModule> EnabledLogCategories;

};
