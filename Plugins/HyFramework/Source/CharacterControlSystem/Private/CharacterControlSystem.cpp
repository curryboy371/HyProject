// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2022. All Rights Reserved. 

#include "CharacterControlSystem.h"

#include "Modules/ModuleManager.h"

#include "HyCoreMacro.h"

#define LOCTEXT_NAMESPACE "FCharacterControlSystem"

// 로그 카테고리 정의는 각 모듈에서 한번만 정의되도록
DEFINE_LOG_CATEGORY(CharacterControlSystem);

void FCharacterControlSystem::StartupModule()
{
}

void FCharacterControlSystem::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCharacterControlSystem, CharacterControlSystem);