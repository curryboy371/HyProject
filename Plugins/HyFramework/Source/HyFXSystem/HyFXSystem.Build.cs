// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

using System.IO;
using UnrealBuildTool;

public class HyFXSystem : ModuleRules
{
	public HyFXSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //PrivatePCHHeaderFile = "Public/HyFXPch.h";

        PrivateDefinitions.Add($"{Name.ToUpper()}_LOGGING_DEFINED=1");
        PrivateDefinitions.Add($"LOG_CATEGORY_NAME=\"{Name}\"");


        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));



        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "GameplayTags",


				// Custom Modules

            }
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
                "Niagara",

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
