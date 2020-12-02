// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine.h"
#include "ModuleManager.h"
#include "UnrealEd.h"
#include "Interfaces/IMainFrameModule.h"

class FTrapPlacementToolModule : public IModuleInterface {
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void OnGetAllowedClass(TArray<const UClass*>& outclasses);

	TSharedPtr<FExtender> ToolbarExtender;
	TSharedPtr<const FExtensionBase> Extension;

	void MyButton_Clicked();

	void AddToolbarExtension(FToolBarBuilder &builder);

public:
};
