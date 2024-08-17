// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Engine/Engine.h"

#include "HyCoreTypes.h"
#include "HyCoreDefineMacro.h"

#include "HyCoreLoggingEngineSubsystem.generated.h"



typedef UHyCoreLoggingEngineSubsystem UHyLogging;

#pragma region ImplementMacro

// Developer Setting에서 사용할 Framework Log Category OnOff Switch
 // Log Category Enable Define
#define LogCategoryGetEnableMapName LogCategoryGetEnableMap
#define LogCategorySetEnableMapName LogCategorySetEnableMap

#define DEFINE_LOG_CATEGORY_ENABLE_SYSTEM(CategoryName) \
    bool bLogEnable##CategoryName = true; \
public:\
    const bool IsEnable##CategoryName() const { return bLogEnable##CategoryName; }\
    void SetEnable##CategoryName(const bool bEnabled) \
	{ \
		bLogEnable##CategoryName = bEnabled; \
			\
	} \

#define ADD_LOG_CATEGORY(CategoryName) \
    LogCategoryGetEnableMapName.Add(TEXT(#CategoryName), &UHyCoreLoggingEngineSubsystem::IsEnable##CategoryName);\
	LogCategorySetEnableMapName.Add(TEXT(#CategoryName), &UHyCoreLoggingEngineSubsystem::SetEnable##CategoryName);\

#pragma endregion


#pragma region UsingDefineMacro

// Define all log categories
#define DEFINE_LOG_CATEGORIES() \
    LOG_CATEGORY_LIST(DEFINE_LOG_CATEGORY_ENABLE_SYSTEM)

// Add all log categories to map
#define ADD_LOG_ENABLE_CATEGORIES() \
    LOG_CATEGORY_LIST(ADD_LOG_CATEGORY)

#pragma endregion
/**
 * 
 */
UCLASS()
class HYCORE_API UHyCoreLoggingEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
    /** Implement this for initialization of instances of the system */
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /** Implement this for deinitialization of instances of the system */
    virtual void Deinitialize() override;
	
protected:
	void InitLogCategoryEnableMap()
	{
		LogCategoryGetEnableMapName.Empty();
		ADD_LOG_ENABLE_CATEGORIES()
	}

public:

	ELogPrintType GetLogPrintType() const {	return LogPrintType;}
	void SetLogPrintType(const ELogPrintType InLogPrintType) { LogPrintType = InLogPrintType; }


	inline FString GetFilename(const char* InFilePath)
	{
		FString FilePathStr = FString(ANSI_TO_TCHAR(InFilePath)).Replace(TEXT("\\"), TEXT("/"));
		int32 LastSlashIndex;
		if (FilePathStr.FindLastChar('/', LastSlashIndex))
		{
			return FilePathStr.RightChop(LastSlashIndex + 1);
		}
		return FilePathStr;
	}

	// 로그 카테고리 enable 확인
	const bool IsEnableLogCategory(const FString& InCategoryName) const
	{
		if(LogPrintType == ELogPrintType::ELOG_Output_ALL)
		{
			return true;
		}
		else if (LogPrintType == ELogPrintType::ELOG_Hide)
		{
			return false;
		}

		auto FuncPtr = LogCategoryGetEnableMapName.Find(InCategoryName);
		if (FuncPtr && *FuncPtr)
		{
			return (this->**FuncPtr)();
		}

		return false;
	}

	// 로그 카테고리 enable 설정
	void SetLogCategoryEnable(const FString& InCategoryName, const bool bEnabled)
	{
		auto FuncPtr = LogCategorySetEnableMapName.Find(InCategoryName);
		if (FuncPtr && *FuncPtr)
		{
			(this->**FuncPtr)(bEnabled);
		}
	}

protected:
	TMap<FString, const bool(UHyCoreLoggingEngineSubsystem::*)() const> LogCategoryGetEnableMapName;
	TMap<FString, void(UHyCoreLoggingEngineSubsystem::*)(const bool)> LogCategorySetEnableMapName;

	ELogPrintType LogPrintType = ELogPrintType::ELOG_Output_ALL;

	DEFINE_LOG_CATEGORIES()

};
