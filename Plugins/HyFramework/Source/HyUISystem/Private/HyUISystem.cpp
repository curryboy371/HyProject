// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "HyUISystem.h"

#include "Modules/ModuleManager.h"
#include "HyCoreMacro.h"

#define LOCTEXT_NAMESPACE "FHyUISystem"

DEFINE_LOG_CATEGORY(HyFXSystem);

void FHyUISystem::StartupModule()
{
}

void FHyUISystem::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHyUISystem, HyUISystem);