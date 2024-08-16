// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "InventorySystem.h"

#include "Modules/ModuleManager.h"

#include "HyCoreMacro.h"

#define LOCTEXT_NAMESPACE "FInventorySystem"

DEFINE_LOG_CATEGORY(InventorySystem);


void FInventorySystem::StartupModule()
{
}

void FInventorySystem::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInventorySystem, InventorySystem);