// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CurseOfDesireTarget : TargetRules
{
	public CurseOfDesireTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.AddRange(new string[]{"CurseOfDesire", "Characters", "UI", "Trap", "KeeaCameraModule", "KeeaBlockModule"});
	}
}
