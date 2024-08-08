// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

#include "LoggingSystem.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FLoggingSystem"

void FLoggingSystem::StartupModule()
{
}

void FLoggingSystem::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLoggingSystem, LoggingSystem);