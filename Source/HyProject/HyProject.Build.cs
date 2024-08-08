// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class HyProject : ModuleRules
{
	public HyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
        new string[]
        {
            "HyProject",
            "HyProject/Public",
        }
        );

        PrivateIncludePaths.AddRange(
        new string[]
        {
            "HyProject/Private",
        }
        );

        PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
            "GameplayTags",

        });

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"LoggingSystem",


        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
