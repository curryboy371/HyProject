// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class NPTable : ModuleRules
{
	public NPTable(ReadOnlyTargetRules Target) : base(Target)
	{
		
		PrivatePCHHeaderFile = "Public/NPTable.h";

		PCHUsage = PCHUsageMode.UseSharedPCHs;

		PrivateIncludePaths.Add("NPTable/Private");

		PublicIncludePaths.AddRange
		(
			new string[] 
			{
				"NPTable/Public",
				"NPTable/Public/Table"
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"CoreUObject",
				"Engine",
			}
		);
	}
}
