// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WorldMonsterModule.h"
#include "KeeaEditorStyle.h"
#include "WorldMonsterModuleCommands.h"
#include "LevelEditor.h"
#include "SMySceneOutliner.h"
#include "..\Public\WorldMonsterModule.h"

IMPLEMENT_MODULE(FWorldMonsterModule, WorldMonsterModule);

void FWorldMonsterModule::StartupModule()
{
	FWorldMonsterModuleCommands::Register();
	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList());
	CommandList->MapAction(FWorldMonsterModuleCommands::Get().MyButton,
		FExecuteAction::CreateRaw(this, &FWorldMonsterModule::MyButton_Clicked), FCanExecuteAction());

	ToolbarExtender = MakeShareable(new FExtender());

	Extension = ToolbarExtender->AddToolBarExtension("Compile",
		EExtensionHook::Before, CommandList,
		FToolBarExtensionDelegate::CreateRaw(this, &FWorldMonsterModule::AddToolbarExtension));

	FLevelEditorModule & LevelEditorMoudle =
		FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorMoudle.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FWorldMonsterModule::ShutdownModule()
{
	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	Extension.Reset();
	ToolbarExtender.Reset();
}

void FWorldMonsterModule::OnGetAllowedClasses(TArray<const UClass*>& outclasses)
{
	outclasses.Add(UStaticMesh::StaticClass());
}

void FWorldMonsterModule::MyButton_Clicked()
{
	TSharedRef<SWindow> Window = SNew(SWindow).Title(FText::FromString(TEXT("월드배치 몬스터들")))
		.ClientSize(FVector2D(800, 400)).SupportsMaximize(false).SupportsMinimize(false)
		[
			//여기에 콘텐츠를...
			SNew(SMySceneOutliner)
		];

	IMainFrameModule & MainFrameMoudle = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	if (MainFrameMoudle.GetParentWindow().IsValid()) {
		FSlateApplication::Get().AddWindowAsNativeChild(Window, MainFrameMoudle.GetParentWindow().ToSharedRef());
	}
	else {
		FSlateApplication::Get().AddWindow(Window);
	}
}

void FWorldMonsterModule::AddToolbarExtension(FToolBarBuilder & builder)
{
	FSlateIcon IconBrush = FSlateIcon(KeeaEditorStyle::Get().GetStyleSetName(), "Adventure_Map_icon_64");

	builder.AddToolBarButton(FWorldMonsterModuleCommands::Get().MyButton,
		NAME_None, FText::FromString(TEXT("월드배치 몬스터들")),
		FText::FromString(TEXT("현재 월드에 배치된 몬스터들의 설정을 변경할 수 있습니다.")), IconBrush, NAME_None);
}
