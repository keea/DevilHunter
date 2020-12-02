#pragma once
#include "Commands.h"
#include "EditorStyleSet.h"

class FMonsterPlacementCommands : public TCommands<FMonsterPlacementCommands> {
public:
	FMonsterPlacementCommands() : TCommands(FName(TEXT("MonsterPlacement")),
		FText::FromString("Monster Placement"), NAME_None, FEditorStyle::GetStyleSetName()) {
	};

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> MyButton;
};