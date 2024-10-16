// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

using System.IO;
using UnrealBuildTool;


public class ActionsSystem : ModuleRules
{
	public ActionsSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //PrivatePCHHeaderFile = "Public/ActionsPch.h";

        PrivateDefinitions.Add($"{Name.ToUpper()}_LOGGING_DEFINED=1");
        PrivateDefinitions.Add($"LOG_CATEGORY_NAME=\"{Name}\"");
        PrivateDefinitions.Add($"LOG_CATEGORY={Name}");


        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "GameplayTags",

				//Custom Module

				// AIControlSystem depends on ActionsSystem ( AIControlSystem.Build.cs > ActionsSystem.Build.cs )
				"HyFXSystem", // ActionsSystem depends on HyFXSystem ( ActinosTypes.h > HyFXTypes.h )
            }
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
                "DeveloperSettings",

				//Custom Module
                "HyCore",

            }
            );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
			}
			);
	}
}
