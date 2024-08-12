// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class HyProject : ModuleRules
{
	public HyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


        /*       
         *       아래와 같이 include 하는 경우, 모듈 경로가 정확히 추가되지 않아 모호해짐
         *       엔진 경로에서 Public을 찾게되므로 ModuleDirectory를 넣어 Add 해주자
         *       PublicIncludePaths.AddRange(
                new string[]
                {
                    "HyProject/Public",
                }
                );

                PrivateIncludePaths.AddRange(
                new string[]
                {
                    "HyProject/Private",
                }
                );*/

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));


        PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
            "EnhancedInput",
            "GameplayTags",

        });

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"HyCore",


        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
