// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class KEEAMODULE_API KeeaEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static void ReloadTextures();

	static const class ISlateStyle& Get();

private:
	static TSharedRef<class FSlateStyleSet> Create();
	static TSharedPtr<class FSlateStyleSet> StyleInstance;
};
