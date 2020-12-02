// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "KeeaModule.h"
#include "..\Public\KeeaModule.h"
#include "KeeaEditorStyle.h"

IMPLEMENT_MODULE( FKeeaModule, KeeaModule);
 
void FKeeaModule::StartupModule()
{
	//Initialize style
	KeeaEditorStyle::Initialize();
	KeeaEditorStyle::ReloadTextures();
}

void FKeeaModule::ShutdownModule()
{
	KeeaEditorStyle::Shutdown();
}
