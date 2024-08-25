// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class HyFramework : ModuleRules
{
	public HyFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //PrivatePCHHeaderFile = "Public/HyPch.h";
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
                "EnhancedInput",
				"MotionWarping",

                "UMG",


				// Custom Modules
                //"ActionsSystem",


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
                "HyCore",
                "CharacterControlSystem",
                "ActionsSystem",
                "HyFXSystem",
                "CollisionSystem",
				"HyUISystem",
                "InventorySystem",


                "HyTable",

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
