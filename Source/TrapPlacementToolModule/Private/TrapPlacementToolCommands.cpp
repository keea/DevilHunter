#include "TrapPlacementToolCommands.h"
#include "TrapPlacementToolModule.h"
#include "Commands.h"

void FTrapPlacementToolCommands::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(MyButton, "TrapPlacement", "Trap Placement Tool",
		EUserInterfaceActionType::Button, FInputGesture());
#undef LOCTEXT_NAMESPACE
}
