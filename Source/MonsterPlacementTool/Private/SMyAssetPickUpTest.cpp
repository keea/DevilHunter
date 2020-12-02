// Fill out your copyright notice in the Description page of Project Settings.


#include "SMyAssetPickUpTest.h"
#include "MonsterPlacementTool.h"
#include "SlateOptMacros.h"

#include "EditorStyleSet.h"
#include "EditorFontGlyphs.h"
#include "BaseMonsterClass.h"

#include "SBox.h"

#include "AssetData.h"
#include "IContentBrowserSingleton.h"
#include "IDetailsView.h"

#include "ContentBrowserModule.h"
#include "PropertyEditorModule.h"
#include "AssetData.h"

#include "Framework/Docking/TabManager.h"

#include "Editor/EditorEngine.h"

#include "BaseMonsterClass.h"

#include "Toolkits/AssetEditorManager.h"

#define LOCTEXT_NAMESPACE "Keea"

static const FName PosParentClassTagName(TEXT("ParentClass"));
static const FString PosClassTestMonPath(TEXT("Class'/Script/Characters.testMon'"));
static const FString PosClassMiddleBossPath(TEXT("Class'/Script/Characters.CODMiddleBoss'"));
static const FString PosClassBossPath(TEXT("Class'/Script/Characters.CODBossMon'"));


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMyAssetPickUpTest::Construct(const FArguments& InArgs)
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	// Configure filter for asset picker
	FAssetPickerConfig Config;
	Config.Filter.bRecursiveClasses = true;
	Config.OnAssetSelected = FOnAssetSelected::CreateSP(this, &SMyAssetPickUpTest::OnAssetSelectedFromPicker);
	Config.OnAssetDoubleClicked = FOnAssetSelected::CreateSP(this, &SMyAssetPickUpTest::OnAssetDoubleClickedFromPicker);
	Config.Filter.TagsAndValues.Add(PosParentClassTagName, PosClassTestMonPath);
	Config.Filter.TagsAndValues.Add(PosParentClassTagName, PosClassMiddleBossPath);
	Config.Filter.TagsAndValues.Add(PosParentClassTagName, PosClassBossPath);
	Config.InitialAssetViewType = EAssetViewType::Tile;


	FPropertyEditorModule & PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	FDetailsViewArgs propertyConfig;
	propertyConfig.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::ObjectsUseNameArea;
	propertyConfig.bAllowMultipleTopLevelObjects = true;
	DetailsView = PropertyEditorModule.CreateDetailView(propertyConfig);


	ChildSlot
	[
		// Populate the widget
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(SBox)
			[
				SNew(SBorder)
				.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
		[
			
			ContentBrowserModule.Get().CreateAssetPicker(Config)
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
void SMyAssetPickUpTest::OnAssetSelectedFromPicker(const FAssetData & AssetData)
{	
	TArray<UObject*> OutDefaultSubobjects;
	
	AssetData.GetPackage()->GetDefaultSubobjects(OutDefaultSubobjects);
	DetailsView->SetObjects(OutDefaultSubobjects, true);
}

void SMyAssetPickUpTest::OnAssetDoubleClickedFromPicker(const FAssetData & AssetData)
{
	if (UObject * ObjectToEdit = AssetData.GetAsset()) {
		FAssetEditorManager::Get().OpenEditorForAsset(ObjectToEdit);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE