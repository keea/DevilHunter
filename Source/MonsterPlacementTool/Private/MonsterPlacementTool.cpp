// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MonsterPlacementTool.h"
#include "KeeaEditorStyle.h"
#include "LevelEditor.h"
#include "SlateBasics.h"
#include "MonsterPlacementCommands.h"
#include "..\Public\MonsterPlacementTool.h"

#include "Widgets/Docking/SDockTab.h"
#include "SMyAssetPickUpTest.h"

IMPLEMENT_MODULE( FMonsterPlacementToolModule, MonsterPlacementTool);
 
void FMonsterPlacementToolModule::StartupModule()
{
	FMonsterPlacementCommands::Register();
	TSharedPtr<FUICommandList> CommandList =
		MakeShareable(new FUICommandList());
	CommandList->MapAction(FMonsterPlacementCommands::Get().MyButton,
		FExecuteAction::CreateRaw(this, &FMonsterPlacementToolModule::MyButton_Clicked), FCanExecuteAction());
	
	ToolbarExtender = MakeShareable(new FExtender());
	
	Extension = ToolbarExtender->AddToolBarExtension("Compile",
		EExtensionHook::Before, CommandList,
		FToolBarExtensionDelegate::CreateRaw(this, &FMonsterPlacementToolModule::AddToolbarExtension));
	FLevelEditorModule & LevelEditorMoudle =
		FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	LevelEditorMoudle.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FMonsterPlacementToolModule::ShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterAllTabSpawners();
	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	Extension.Reset();
	ToolbarExtender.Reset();
}

void FMonsterPlacementToolModule::OnGetAllowedClasses(TArray<const UClass*>& outclasses)
{
	outclasses.Add(UStaticMesh::StaticClass());
}

void FMonsterPlacementToolModule::MyButton_Clicked()
{
	TSharedRef<SWindow> CookbookWindow = SNew(SWindow).Title(FText::FromString(TEXT("몬스터배치")))
		.ClientSize(FVector2D(800, 400)).SupportsMaximize(false).SupportsMinimize(false)
		[
			SNew(SMyAssetPickUpTest)
		]
	;

	IMainFrameModule & MainFrameModule =
		FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	if (MainFrameModule.GetParentWindow().IsValid()) {
		FSlateApplication::Get().AddWindowAsNativeChild(CookbookWindow,
			MainFrameModule.GetParentWindow().ToSharedRef());
	}
	else {
		FSlateApplication::Get().AddWindow(CookbookWindow);
	}
}

void FMonsterPlacementToolModule::AddToolbarExtension(FToolBarBuilder & builder)
{
	FSlateIcon IconBrush = FSlateIcon(KeeaEditorStyle::Get().GetStyleSetName(), "Monster_icon_64");

	builder.AddToolBarButton(FMonsterPlacementCommands::Get().MyButton,
		NAME_None, FText::FromString(TEXT("몬스터 배치")),
		FText::FromString(TEXT("현재 화면 위치에서 몬스터를 배치 합니다.")), IconBrush, NAME_None);
}
