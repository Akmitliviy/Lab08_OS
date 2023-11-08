// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WinProcesses : ModuleRules
{
	public WinProcesses(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "ICU" });

		PublicDefinitions.Add("_WIN32_WINNT_WIN10_TH2");
		PublicDefinitions.Add("_WIN32_WINNT_WIN10_RS1");
		PublicDefinitions.Add("_WIN32_WINNT_WIN10_RS2");
		PublicDefinitions.Add("_WIN32_WINNT_WIN10_RS3");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
