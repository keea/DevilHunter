// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TrapPlacementToolModule.h"
#include "KeeaEditorStyle.h"
#include "LevelEditor.h"
#include "SlateBasics.h"
#include "..\Public\TrapPlacementToolModule.h"
#include "TrapPlacementToolCommands.h"

#include "TrapEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"

#include "STrapAssetPickUp.h"


IMPLEMENT_MODULE(FTrapPlacementToolModule, TrapPlacementToolModule);


void FTrapPlacementToolModule::StartupModule()
{
	FTrapPlacementToolCommands::Register();
	TSharedPtr<FUICommandList> CommandList =
		MakeShareable(new FUICommandList());
	CommandList->MapAction(FTrapPlacementToolCommands::Get().MyButton,
		FExecuteAction::CreateRaw(this, &FTrapPlacementToolModule::MyButton_Clicked), FCanExecuteAction());

	ToolbarExtender = MakeShareable(new FExtender());

	Extension = ToolbarExtender->AddToolBarExtension("Compile",
		EExtensionHook::Before, CommandList,
		FToolBarExtensionDelegate::CreateRaw(this, &FTrapPlacementToolModule::AddToolbarExtension));
	FLevelEditorModule & LevelEditorMoudle =
		FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorMoudle.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FTrapPlacementToolModule::ShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterAllTabSpawners();
	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	Extension.Reset();
	ToolbarExtender.Reset();
}

void FTrapPlacementToolModule::OnGetAllowedClass(TArray<const UClass*>& outclasses)
{
	outclasses.Add(UStaticMesh::StaticClass());
}

void FTrapPlacementToolModule::MyButton_Clicked()
{
	IMainFrameModule & MainFrameModule =
		FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));


	TSharedRef<SWindow> CookbookWindow = SNew(SWindow).Title(FText::FromString(TEXT("함정배치")))
		.ClientSize(FVector2D(800, 400)).SupportsMaximize(false).SupportsMinimize(false)
		[
			SNew(STrapAssetPickUp)
		];
	
	if (MainFrameModule.GetParentWindow().IsValid()) {
		FSlateApplication::Get().AddWindowAsNativeChild(CookbookWindow,
			MainFrameModule.GetParentWindow().ToSharedRef());
	}
	else {
		FSlateApplication::Get().AddWindow(CookbookWindow);
	}
}

void FTrapPlacementToolModule::AddToolbarExtension(FToolBarBuilder & builder)
{
	FSlateIcon IconBrush = FSlateIcon(KeeaEditorStyle::Get().GetStyleSetName(), "Bomb_icon_64");

	builder.AddToolBarButton(FTrapPlacementToolCommands::Get().MyButton,
		NAME_None, FText::FromString(TEXT("트랩 배치")),
		FText::FromString(TEXT("현재 화면 위치에서 트랩 배치 합니다.")), IconBrush, NAME_None);
}
