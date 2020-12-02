// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MonsterPlacementTool : ModuleRules
{
	public MonsterPlacementTool(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
		"RHI", "RenderCore", "MainFrame", "EditorStyle", "Characters"});
		//PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd"}); 
		if (Target.Type == TargetRules.TargetType.Editor)
    	{
       		PrivateDependencyModuleNames.AddRange( new string[] { "UnrealEd","KeeaModule" });
    	}

		if ( (Target.Type == TargetRules.TargetType.Client) || (Target.Type == TargetRules.TargetType.Editor))
		{
			 PrivateDependencyModuleNames.AddRange( new string[] { "Slate", "SlateCore" });
		}
	}
}
