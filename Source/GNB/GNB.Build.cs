// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;


public class GNB : ModuleRules
{
	public GNB(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		//PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG"});
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	
		PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "../inc/")));
		PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "../inc/YCNW")));


		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}