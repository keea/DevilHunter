#pragma once
#include "Commands.h"
#include "EditorStyleSet.h"

class FTrapPlacementToolCommands : public TCommands<FTrapPlacementToolCommands> {
public:
	FTrapPlacementToolCommands() : TCommands(FName(TEXT("TrapPlacement")),
		FText::FromString("Trap Placement"), NAME_None, FEditorStyle::GetStyleSetName()) {
	};

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> MyButton;
};