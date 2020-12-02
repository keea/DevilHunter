// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WorldTrapModule : ModuleRules
{
	public WorldTrapModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
		"RHI", "RenderCore", "MainFrame",  "EditorStyle", "Trap"});

		if (Target.Type == TargetRules.TargetType.Editor)
    	{
       		PrivateDependencyModuleNames.AddRange( new string[] { "UnrealEd","SceneOutliner","LevelEditor", "KeeaModule"});
    	}

		 if ( (Target.Type == TargetRules.TargetType.Client) || (Target.Type == TargetRules.TargetType.Editor))
		 {
			 PrivateDependencyModuleNames.AddRange( new string[] { "Slate", "SlateCore" });
		 }

		//PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "SceneOutliner", "LevelEditor" }); 
	}
}
