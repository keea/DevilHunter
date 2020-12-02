#pragma once
#include "Commands.h"
#include "EditorStyleSet.h"

class FWorldMonsterModuleCommands : public TCommands<FWorldMonsterModuleCommands> {
public:
	FWorldMonsterModuleCommands() : TCommands(FName(TEXT("WorldMonsterModule")),
		FText::FromString("World Monster Module"), NAME_None, FEditorStyle::GetStyleSetName()) {
	};

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> MyButton;
};