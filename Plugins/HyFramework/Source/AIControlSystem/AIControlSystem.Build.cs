// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2022. All Rights Reserved. 

using System.IO;
using UnrealBuildTool;

public class AIControlSystem : ModuleRules
{
	public AIControlSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
        new string[]
        {
            "AIControlSystem",
            "AIControlSystem/Public",
        }
        );


        PrivateIncludePaths.AddRange(
        new string[]
        {
            "AIControlSystem/Private",
        }
        );


        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",

			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
			}
			);
	}
}
