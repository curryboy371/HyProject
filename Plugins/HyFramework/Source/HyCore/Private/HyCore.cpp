// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "HyCore.h"

#include "Modules/ModuleManager.h"

#include "HyCoreLogging.h"

#define LOCTEXT_NAMESPACE "FHyCore"

// 로그 카테고리 정의는 각 모듈에서 한번만 정의되도록
DEFINE_LOG_CATEGORY(HyCore);


void FHyCore::StartupModule()
{
}

void FHyCore::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHyCore, HyCore);