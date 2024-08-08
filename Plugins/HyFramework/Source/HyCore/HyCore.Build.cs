// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

using System.IO;
using UnrealBuildTool;

public class HyCore : ModuleRules
{
	public HyCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
         new string[]
         {
            "HyCore/Public",
         }
         );


        PrivateIncludePaths.AddRange(
        new string[]
        {
            "HyCore/Private",
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
