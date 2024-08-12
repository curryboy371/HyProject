// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

using System.IO;
using UnrealBuildTool;

public class CollisionSystem : ModuleRules
{
	public CollisionSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //PrivatePCHHeaderFile = "Public/CollisionPch.h";

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
