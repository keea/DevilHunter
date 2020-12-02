// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KeeaModule : ModuleRules
{
	public KeeaModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
		"RHI", "RenderCore", "MainFrame", "EditorStyle"});
		//PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd" }); 
		if (Target.Type == TargetRules.TargetType.Editor)
    	{
       		PrivateDependencyModuleNames.AddRange( new string[] { "UnrealEd"});
    	}

		if ( (Target.Type == TargetRules.TargetType.Client) || (Target.Type == TargetRules.TargetType.Editor))
		{
			 PrivateDependencyModuleNames.AddRange( new string[] { "Slate", "SlateCore" });
		}
	}
}
