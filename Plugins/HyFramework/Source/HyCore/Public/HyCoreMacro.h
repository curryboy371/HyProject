// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HyCoreLoggingEngineSubsystem.h"

/**
 *   macro 
 */

 // 로그를 매크로로 사용하기 위해 전처리기 매크로 지정
 // 파일이름, Function 등을 매크로를 남기는 위치로 지정하고, 카테고리를 해당 위치가 속해있는 모듈 카테고리로 지정하기 위해서
 // include로 사용하는 header에서 macro를 사용함.

#pragma region LogCategoryDeclare
// 로깅 카테고리 Declare 매크로
//  로그 사용시 include를 HyCoreMacro.h만 하기 위해 선언은 여기서, 정의는 각 모듈에서 이루어짐.
DECLARE_LOG_CATEGORY_EXTERN(HyFramework, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HyCore, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ActionsSystem, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(AIControlSystem, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(CharacterControlSystem, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(CollisionSystem, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(InventorySystem, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HyUISystem, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HyFXSystem, Log, All);
//////////////////////////////
#pragma endregion

#define GET_TAG_SUBSYSTEM() (GEngine->GetEngineSubsystem<UHyTagSubsystem>())

#pragma region LogUsingMacro
// 실제 로그 사용과 관련된 매크로

#define GET_LOGGING_SUBSYSTEM (GEngine->GetEngineSubsystem<UHyCoreLoggingEngineSubsystem>())

#define __FILENAME__ (GET_LOGGING_SUBSYSTEM->GetFilename(__FILE__))
#define __FUNCNAME__  ANSI_TO_TCHAR(__FUNCTION__)

// DeveloperSetting에서 Category enable bool 값이 true인지 check하여 출력 여부를 결정
#define IS_ENABLE_LOG(CategoryName) (GEngine && GET_LOGGING_SUBSYSTEM) ? GET_LOGGING_SUBSYSTEM->IsEnableLogCategory(CategoryName) : false


#define LOG_V(Fmt, ...) if (IS_ENABLE_LOG(LOG_CATEGORY_NAME)) UE_LOG(LOG_CATEGORY, Log,		TEXT("[LOG] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)
#define WAR_V(Fmt, ...) if (IS_ENABLE_LOG(LOG_CATEGORY_NAME)) UE_LOG(LOG_CATEGORY, Warning,	TEXT("[WAR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)
#define LOG_I           if (IS_ENABLE_LOG(LOG_CATEGORY_NAME)) UE_LOG(LOG_CATEGORY, Log,		TEXT("[LOG]  ...[%s::%s(%d)]"), *__FILENAME__, __FUNCNAME__, __LINE__)
#define LOG_D(Fmt, ...) if (IS_ENABLE_LOG(LOG_CATEGORY_NAME)) UE_LOG(LOG_CATEGORY, Log,		TEXT(Fmt), ##__VA_ARGS__)
#define ERR_V(Fmt, ...) if (IS_ENABLE_LOG(LOG_CATEGORY_NAME)) UE_LOG(LOG_CATEGORY, Error,	TEXT("[ERR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)

#define LOG_GUARD			FLogGuard(TEXT("  ...") + FString(__FILENAME__) + TEXT("::") + __FUNCTION__)
#define LOG_GUARD_V(str)	FLogGuard logGuard(FString(str) + TEXT("  ...") + FString(__FILENAME__) + TEXT("::") + __FUNCTION__)

#define SCREEN_LOG_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("[LOG] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__))
#define SCREEN_WAR_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("[WAR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__))
#define SCREEN_ERR_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("[ERR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__))


// FLogGuard 구조체 정의
// 생성자 소멸자에서 로그 출력
struct FLogGuard
{
	FLogGuard(FString InStr)
		: FunctionName(InStr)
	{
		//LOG_D("[Start] %s", *FunctionName);
	}

	~FLogGuard()
	{
		//LOG_D("[End] %s", *FunctionName);
	}

private:
	FString FunctionName; // 함수 이름을 저장하는 변수
};


// 로그 카테고리가 없는 모듈은 디폴트 카테고리로

#pragma endregion














