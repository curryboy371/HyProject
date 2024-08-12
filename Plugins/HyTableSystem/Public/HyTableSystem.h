// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Engine/Engine.h"

/** Module interface for this game's loading screens */
class FHyTableModule : public IModuleInterface
{
public:
	/** Loads the module so it can be turned on */
	static inline FHyTableModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FHyTableModule>("HyTable");
	}

};
