// Fill out your copyright notice in the Description page of Project Settings.


#include "SMySceneOutliner.h"
#include "SlateOptMacros.h"

#include "EditorStyleSet.h"
#include "EditorFontGlyphs.h"

#include "SBox.h"
#include "Widgets/Layout/SBorder.h"

#include "Modules/ModuleManager.h"

#include "PropertyEditorModule.h"
#include "SceneOutlinerModule.h"

#include "Editor/EditorEngine.h"
#include "ActorTreeItem.h"

#include "BaseMonsterClass.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMySceneOutliner::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule & PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	
	FDetailsViewArgs propertyConfig;
	propertyConfig.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::ObjectsUseNameArea;
	propertyConfig.bAllowMultipleTopLevelObjects = true;
	DetailsView = PropertyEditorModule.CreateDetailView(propertyConfig);

	//SceneOutliner 옵션 설정
	FSceneOutlinerModule & SceneOutlinerModule = FModuleManager::Get().LoadModuleChecked<FSceneOutlinerModule>(TEXT("SceneOutliner"));
	SceneOutliner::FInitializationOptions InitOptions;
	{
		InitOptions.Mode = ESceneOutlinerMode::ActorPicker;

		// We hide the header row to keep the UI compact.
		// @todo: Might be useful to have this sometimes, actually.  Ideally the user could summon it.
		InitOptions.bShowHeaderRow = true;

		struct Local
		{
			static bool IsMonsterActor(const AActor* const Actor)
			{
				return Actor->IsA(ABaseMonsterClass::StaticClass());
			}
		};

		// Only display Matinee actors
		InitOptions.Filters->AddFilterPredicate(SceneOutliner::FActorFilterPredicate::CreateStatic(&Local::IsMonsterActor));
	}

	SceneOutliner = SceneOutlinerModule.CreateSceneOutliner(InitOptions,
		FOnSceneOutlinerItemPicked::CreateSP(this, &SMySceneOutliner::OnSceneOutlinerItemClicked));

	
	ChildSlot
	[
		// Populate the widget
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(SBox)
			[
				SNew(SBorder)
				.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
		[
			SceneOutliner.ToSharedRef()
		]
			]
		]
	+ SHorizontalBox::Slot()
		[
			SNew(SBox)
			[
				SNew(SBorder)
				.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
		[
			DetailsView.ToSharedRef()
		]
			]
		]
	];
	
}
void SMySceneOutliner::OnSceneOutlinerItemClicked(TSharedRef<SceneOutliner::ITreeItem> Item)
{
	Item->Visit(
		SceneOutliner::FFunctionalVisitor()
		.Actor([&](const  SceneOutliner::FActorTreeItem& ActorItem) {
		if (AActor* Actor = ActorItem.Actor.Get())
		{
			DetailsView->SetObject(Actor);
			const bool bActiveViewportOnly = false;
			GEditor->MoveViewportCamerasToActor(*Actor, bActiveViewportOnly);
		}
	})
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
