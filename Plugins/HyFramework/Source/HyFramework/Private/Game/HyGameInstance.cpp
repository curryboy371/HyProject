// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HyGameInstance.h"

#include "HyCoreLogging.h"

void UHyGameInstance::Init()
{
	UGameInstance::Init();
	LOG_V("LogTest");



	LOG_GUARD;

	LOG_GUARD_V("teset");

}
