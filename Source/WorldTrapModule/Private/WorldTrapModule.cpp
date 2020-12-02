// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WorldTrapModule.h"

#include "KeeaEditorStyle.h"
#include "WorldTrapModuleCommands.h"
#include "STrapSceneOutliner.h"

#include "LevelEditor.h"

#include "..\Public\WorldTrapModule.h"

IMPLEMENT_MODULE( FWorldTrapModule, WorldTrapModule);
 
void FWorldTrapModule::StartupModule()
{
	FWorldTrapModuleCommands::Register();
	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList());
	CommandList->MapAction(FWorldTrapModuleCommands::Get().MyButton,
		FExecuteAction::CreateRaw(this, &FWorldTrapModule::MyButton_Clicked), FCanExecuteAction());

	ToolbarExtender = MakeShareable(new FExtender());

	Extension = ToolbarExtender->AddToolBarExtension("Compile",
		EExtensionHook::Before, CommandList,
		FToolBarExtensionDelegate::CreateRaw(this, &FWorldTrapModule::AddToolbarExtension));

	FLevelEditorModule & LevelEditorMoudle =
		FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorMoudle.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FWorldTrapModule::ShutdownModule()
{
	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	Extension.Reset();
	ToolbarExtender.Reset();
}

void FWorldTrapModule::OnGetAllowedClasses(TArray<const UClass*>& outclasses)
{
	outclasses.Add(UStaticMesh::StaticClass());
}

void FWorldTrapModule::MyButton_Clicked()
{
	TSharedRef<SWindow> Window = SNew(SWindow).Title(FText::FromString(TEXT("월드배치 트랩들")))
		.ClientSize(FVector2D(800, 400)).SupportsMaximize(false).SupportsMinimize(false)
		[
			//여기에 콘텐츠를...
			SNew(STrapSceneOutliner)
		];

	IMainFrameModule & MainFrameMoudle = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	if (MainFrameMoudle.GetParentWindow().IsValid()) {
		FSlateApplication::Get().AddWindowAsNativeChild(Window, MainFrameMoudle.GetParentWindow().ToSharedRef());
	}
	else {
		FSlateApplication::Get().AddWindow(Window);
	}
}

void FWorldTrapModule::AddToolbarExtension(FToolBarBuilder & builder)
{
	FSlateIcon IconBrush = FSlateIcon(KeeaEditorStyle::Get().GetStyleSetName(), "Adventure_Map_icon_64");

	builder.AddToolBarButton(FWorldTrapModuleCommands::Get().MyButton,
		NAME_None, FText::FromString(TEXT("월드배치 트랩들")),
		FText::FromString(TEXT("현재 월드에 배치된 트랩들의 설정을 변경할 수 있습니다.")), IconBrush, NAME_None);
}
