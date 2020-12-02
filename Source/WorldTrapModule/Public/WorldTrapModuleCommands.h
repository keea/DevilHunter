#pragma once
#include "Commands.h"
#include "EditorStyleSet.h"

class FWorldTrapModuleCommands : public TCommands<FWorldTrapModuleCommands> {
public:
	FWorldTrapModuleCommands() : TCommands(FName(TEXT("WorldTrap")),
		FText::FromString("World Trap Module"), NAME_None, FEditorStyle::GetStyleSetName()) {
	};

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> MyButton;
};