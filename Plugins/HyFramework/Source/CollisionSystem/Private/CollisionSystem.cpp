// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "CollisionSystem.h"

#include "Modules/ModuleManager.h"

#include "HyCoreMacro.h"

#define LOCTEXT_NAMESPACE "FCollisionSystem"

// 로그 카테고리 정의는 각 모듈에서 한번만 정의되도록
DEFINE_LOG_CATEGORY(CollisionSystem);

void FCollisionSystem::StartupModule()
{
}

void FCollisionSystem::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCollisionSystem, CollisionSystem);