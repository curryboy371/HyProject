// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2022. All Rights Reserved. 

using System.IO;
using UnrealBuildTool;

public class AIControlSystem : ModuleRules
{
	public AIControlSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //PrivatePCHHeaderFile = "Public/AIControlPch.h";
        PrivateDefinitions.Add($"{Name.ToUpper()}_LOGGING_DEFINED=1");

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));



        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "GameplayTags",

            }
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",



				// Custom Modules
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
