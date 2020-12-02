// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KeeaBlockModule : ModuleRules
{
	public KeeaBlockModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "CurseOfDesire" });
		PrivateDependencyModuleNames.AddRange(new string[] { }); 
	}
}
