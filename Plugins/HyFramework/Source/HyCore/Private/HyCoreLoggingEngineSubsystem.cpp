// Fill out your copyright notice in the Description page of Project Settings.


#include "HyCoreLoggingEngineSubsystem.h"

#include "HyCoreDeveloperSettings.h"


void UHyCoreLoggingEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//HyLogDebugWidget = nullptr;

	// file 처리

	InitLogCategoryEnableMap();
}

void UHyCoreLoggingEngineSubsystem::Deinitialize()
{
	// file 처리
}





