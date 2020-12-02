// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Characters : ModuleRules
{
	public Characters(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "CurseOfDesire", "Niagara", "AIModule", "UI" }); 
		PrivateDependencyModuleNames.AddRange(new string[] {  }); 
	}
}
