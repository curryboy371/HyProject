// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "CollisionSystem.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FCollisionSystem"

void FCollisionSystem::StartupModule()
{
}

void FCollisionSystem::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCollisionSystem, CollisionSystem);