// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


#pragma region Log


#define LoggingTag LogTemp

// LOG_I : 클래스::함수(라인) 출력
// LOG_V("text %d", num... ) : 클래스::함수(라인)  + "..." 출력
// LOG_GUARD : lockgard처럼 log 출력

// 유틸리티 함수 정의
inline FString GetCleanFilename(const char* FilePath)
{
	FString FilePathStr = FString(ANSI_TO_TCHAR(FilePath)).Replace(TEXT("\\"), TEXT("/"));
	int32 LastSlashIndex;
	if (FilePathStr.FindLastChar('/', LastSlashIndex))
	{
		return FilePathStr.RightChop(LastSlashIndex + 1);
	}
	return FilePathStr;
}


#define __FILENAME__ (GetCleanFilename(__FILE__))
#define __FUNCNAME__  ANSI_TO_TCHAR(__FUNCTION__)

#if UE_BUILD_SHIPPING
// Shipping에서는 출력을 무시할 log
#define LOG_V(Fmt, ...)
#define WAR_V(Fmt, ...)
#define LOG_I
#define LOG_D(Fmt, ...)
#define ERR_V(Fmt, ...)

#define LOG_GUARD
#define LOG_GUARD_STR(str)

#define SCREEN_LOG_V(Fmt, ...)
#define SCREEN_WAR_V(Fmt, ...)
#define SCREEN_ERR_V(Fmt, ...)

#else

#define LOG_V(Fmt, ...) UE_LOG(LoggingTag, Log, TEXT("[LOG] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)
#define WAR_V(Fmt, ...) UE_LOG(LoggingTag, Warning, TEXT("[WAR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)
#define LOG_I           UE_LOG(LoggingTag, Log, TEXT("[LOG]  ...[%s::%s(%d)]"), *__FILENAME__, __FUNCNAME__, __LINE__)
#define LOG_D(Fmt, ...) UE_LOG(LoggingTag, Log, TEXT(Fmt), ##__VA_ARGS__)

#define LOG_GUARD			FLogGuard(TEXT("  ...") + FString(__FILENAME__) + TEXT("::") + __FUNCTION__)
#define LOG_GUARD_STR(str) FLogGuard logGuard(FString(str) + TEXT("  ...") + FString(__FILENAME__) + TEXT("::") + __FUNCTION__)

#endif
#define ERR_V(Fmt, ...) UE_LOG(LoggingTag, Error, TEXT("[ERR] " Fmt "  ...[%s::%s(%d)]"), ##__VA_ARGS__, *__FILENAME__, __FUNCNAME__, __LINE__)

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
		LOG_D("[Start] %s", *FunctionName);
	}

	~FLogGuard()
	{
		LOG_D("[End] %s", *FunctionName);
	}

private:
	FString FunctionName; // 함수 이름을 저장하는 변수
};



#pragma endregion
