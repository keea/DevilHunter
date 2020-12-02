#include "WorldMonsterModuleCommands.h"
#include "WorldMonsterModule.h"
#include "Commands.h"

void FWorldMonsterModuleCommands::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(MyButton, "WorldMonster", "World Monster Command",
		EUserInterfaceActionType::Button, FInputGesture());
#undef LOCTEXT_NAMESPACE
}