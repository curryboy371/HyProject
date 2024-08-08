// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class HyFramework : ModuleRules
{
	public HyFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


		PublicIncludePaths.AddRange(
		new string[] 
		{
            "HyFramework",
            "HyFramework/Public",
		}
		);
				
		
		PrivateIncludePaths.AddRange(
		new string[] 
		{
            "HyFramework/Private",
        }
        );
   
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "GameplayTags",

                //"LoggingSystem",

				// ... add other public dependencies that you statically link with here ...
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "DeveloperSettings",



				// Custom Modules
                "LoggingSystem",

				// ... add private dependencies that you statically link with here ...	
			}
            );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
