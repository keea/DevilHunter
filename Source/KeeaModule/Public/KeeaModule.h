// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine.h"
#include "ModuleManager.h"
#include "UnrealEd.h"
#include "Interfaces/IMainFrameModule.h"

class FKeeaModule : public IModuleInterface {
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
