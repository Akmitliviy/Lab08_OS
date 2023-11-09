// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class WinProcessesTarget : TargetRules
{
	public WinProcessesTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "WinProcesses" } );
        
		bOverrideBuildEnvironment = true; 
		AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
	}
}
