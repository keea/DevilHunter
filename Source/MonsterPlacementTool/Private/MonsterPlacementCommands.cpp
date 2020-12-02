#include "MonsterPlacementCommands.h"
#include "MonsterPlacementTool.h"
#include "Commands.h"

void FMonsterPlacementCommands::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(MyButton, "Cookbook", "Demo Cookbook Toolbar Command",
		EUserInterfaceActionType::Button, FInputGesture());
#undef LOCTEXT_NAMESPACE
}
