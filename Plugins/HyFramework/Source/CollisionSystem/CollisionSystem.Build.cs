// Copyright (C) Developed by Pask, Published by Dark Tower Interactive SRL 2021. All Rights Reserved. 

using System.IO;
using UnrealBuildTool;

public class CollisionSystem : ModuleRules
{
	public CollisionSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
         new string[]
         {
            "CollisionSystem",
            "CollisionSystem/Public",
         }
         );


        PrivateIncludePaths.AddRange(
        new string[]
        {
            "CollisionSystem/Private",
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
