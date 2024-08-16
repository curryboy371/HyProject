// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "ActionsSystem.h"

#include "Modules/ModuleManager.h"

#include "HyCoreMacro.h"

#define LOCTEXT_NAMESPACE "FActionsSystem"

// 로그 카테고리 정의는 각 모듈에서 한번만 정의되도록
DEFINE_LOG_CATEGORY(ActionsSystem);

void FActionsSystem::StartupModule()
{
}

void FActionsSystem::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FActionsSystem, ActionsSystem);