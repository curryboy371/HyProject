// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyCoreDeveloperSettings.h"

/**
 * 
 */


#pragma region Log

// 로깅 카테고리 선언 추가/////////////////
//  로그 사용시 include를 HyCoreLogging.h만 하기 위해 선언은 여기서, 정의는 각 모듈에서 이루어짐.

//DECLARE_LOG_CATEGORY_EXTERN(HyCore, Log, All);
//DECLARE_LOG_CATEGORY_EXTERN(ActionsSystem, Log, All);
//DECLARE_LOG_CATEGORY_EXTERN(HyFramework, Log, All);
//////////////////////////////


 // 전처리기 디파인된 모듈이름으로 로그 카테고리 탐색
//#ifdef HYFRAMEWORK_LOGGING_DEFINED
//#define CUR_MODULE EHyModule::EHyModule_HyFramework
//#define CUR_LOG_CATEGORY HyFramework
//#endif
//
//#ifdef HYCORE_LOGGING_DEFINED
//#define CUR_MODULE EHyModule::EHyModule_HyCore
//#define CUR_LOG_CATEGORY HyCore
//#define LOG_CATEGORY "HyCore"
//#endif
//
//#ifdef ACTIONSSYSTEM_LOGGING_DEFINED
//#define CUR_MODULE EHyModule::EHyModule_HyCore
//#define CUR_LOG_CATEGORY ActionsSystem
//#endif
//
//// 로그 카테고리가 없는 모듈은 디폴트 카테고리로
//#ifndef CUR_LOG_CATEGORY
//#define CUR_LOG_CATEGORY LogTemp
//#endif

///////////////////

// 로그 카테고리 enable 
//inline bool IsLogCategoryEnabled(FString InCategoryName)
//{
//	if (const UHyCoreDeveloperSettings* Settings = UHyCoreDeveloperSettings::GetDeveloperSetting())
//	{
//		return Settings->IsLogCategoryEnabled(InCategoryName);
//	}
//
//	return false;
//}



// LOG_I : 클래스::함수(라인) 출력
// LOG_V("text %d", num... ) : 클래스::함수(라인)  + "..." 출력
// LOG_GUARD : lockgard처럼 log 출력

// 유틸리티 함수 정의
//inline FString GetCleanFilename(const char* FilePath)
//{
//	FString FilePathStr = FString(ANSI_TO_TCHAR(FilePath)).Replace(TEXT("\\"), TEXT("/"));
//	int32 LastSlashIndex;
//	if (FilePathStr.FindLastChar('/', LastSlashIndex))
//	{
//		return FilePathStr.RightChop(LastSlashIndex + 1);
//	}
//	return FilePathStr;
//}


//#define __FILENAME__ (GetCleanFilename(__FILE__))
//#define __FUNCNAME__  ANSI_TO_TCHAR(__FUNCTION__)

//#if UE_BUILD_SHIPPING
//#if true
//// Shipping에서는 출력을 무시할 log
//#define LOG_V(Fmt, ...)
//#define WAR_V(Fmt, ...)
//#define LOG_I
//#define LOG_D(Fmt, ...)
//#define ERR_V(Fmt, ...)
//
//#define LOG_GUARD
//#define LOG_GUARD_V(str)
//
//#define SCREEN_LOG_V(Fmt, ...)
//#define SCREEN_WAR_V(Fmt, ...)
//#define SCREEN_ERR_V(Fmt, ...)
//
//#else
//
//// LOG_CATEGORY_NAME은 build.cs에서 모듈 이름을 문자열로 넣어준다.
//
//#define LOG_V(Fmt, ...) if (IsLogCategoryEnabled(LOG_CATEGORY_NAME)) UE_LOG(CUR_LOG_CATEGORY, Log, TEXT("[LOG] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)
//#define WAR_V(Fmt, ...) if (IsLogCategoryEnabled(LOG_CATEGORY_NAME)) UE_LOG(CUR_LOG_CATEGORY, Warning, TEXT("[WAR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)
//#define LOG_I           if (IsLogCategoryEnabled(LOG_CATEGORY_NAME)) UE_LOG(CUR_LOG_CATEGORY, Log, TEXT("[LOG]  ...[%s::%s(%d)]"), *__FILENAME__, __FUNCNAME__, __LINE__)
//#define LOG_D(Fmt, ...) if (IsLogCategoryEnabled(LOG_CATEGORY_NAME)) UE_LOG(CUR_LOG_CATEGORY, Log, TEXT(Fmt), ##__VA_ARGS__)
//#define ERR_V(Fmt, ...) if (IsLogCategoryEnabled(LOG_CATEGORY_NAME))UE_LOG(CUR_LOG_CATEGORY, Error, TEXT("[ERR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)
//
//#define LOG_GUARD			FLogGuard(TEXT("  ...") + FString(__FILENAME__) + TEXT("::") + __FUNCTION__)
//#define LOG_GUARD_V(str) FLogGuard logGuard(FString(str) + TEXT("  ...") + FString(__FILENAME__) + TEXT("::") + __FUNCTION__)
//
//#define SCREEN_LOG_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("[LOG] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__))
//#define SCREEN_WAR_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("[WAR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__))
//#define SCREEN_ERR_V(Fmt, ...) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("[ERR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__))
//
//#endif

#pragma endregion
