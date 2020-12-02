// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CurseOfDesireEditorTarget : TargetRules
{
	public CurseOfDesireEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.AddRange(new string[]{"CurseOfDesire", "Characters", "UI", "MonsterPlacementTool","WorldMonsterModule","KeeaModule", "Trap","TrapPlacementToolModule", "WorldTrapModule", "KeeaCameraModule","KeeaBlockModule"});
	}
}
