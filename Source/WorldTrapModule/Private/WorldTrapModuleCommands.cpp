#include "WorldTrapModuleCommands.h"
#include "WorldTrapModule.h"
#include "Commands.h"

void FWorldTrapModuleCommands::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(MyButton, "WorldTrapModule", "World Monster Command",
		EUserInterfaceActionType::Button, FInputGesture());
#undef LOCTEXT_NAMESPACE
}