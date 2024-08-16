// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "HyFXSystem.h"

#include "Modules/ModuleManager.h"

#include "HyCoreMacro.h"


#define LOCTEXT_NAMESPACE "FHyFXSystem"

DEFINE_LOG_CATEGORY(HyFXSystem);

void FHyFXSystem::StartupModule()
{
}

void FHyFXSystem::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHyFXSystem, HyFXSystem);