// Fill out your copyright notice in the Description page of Project Settings.


#include "STrapAssetPickUp.h"
#include "SlateOptMacros.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

#include "PropertyEditorModule.h"

#include "SBox.h"
#include "Widgets/Layout/SBorder.h"

#include "Toolkits/AssetEditorManager.h"

#define LOCTEXT_NAMESPACE "Keea"

static const FName PosParentClassTagName(TEXT("ParentClass"));
static const FString PosClassRockfallTrapPath(TEXT("Class'/Script/Trap.RockfallTrap'"));
static const FString PosClassToxicPlantTrapPath(TEXT("Class'/Script/Trap.ToxicPlantTrap'"));

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STrapAssetPickUp::Construct(const FArguments& InArgs)
{
	//콘텐츠 브라우저 모듈
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	// Configure filter for asset picker
	FAssetPickerConfig Config;
	Config.Filter.bRecursiveClasses = true;
	Config.OnAssetSelected = FOnAssetSelected::CreateSP(this, &STrapAssetPickUp::OnAssetSelectedFromPicker);
	Config.Filter.TagsAndValues.Add(PosParentClassTagName, PosClassRockfallTrapPath);
	Config.Filter.TagsAndValues.Add(PosParentClassTagName, PosClassToxicPlantTrapPath);
	Config.OnAssetDoubleClicked = FOnAssetSelected::CreateSP(this, &STrapAssetPickUp::OnAssetDoubleClickedFromPicker);
	Config.InitialAssetViewType = EAssetViewType::Tile;

	//프로퍼티 에디터 모듈
	FPropertyEditorModule & PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	FDetailsViewArgs propertyConfig;
	propertyConfig.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::ObjectsUseNameArea;
	propertyConfig.bAllowMultipleTopLevelObjects = true;
	DetailsView = PropertyEditorModule.CreateDetailView(propertyConfig);

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
void STrapAssetPickUp::OnAssetSelectedFromPicker(const FAssetData & AssetData)
{
	TArray<UObject*> OutDefaultSubobjects;

	AssetData.GetPackage()->GetDefaultSubobjects(OutDefaultSubobjects);
	DetailsView->SetObjects(OutDefaultSubobjects, true);
}

void STrapAssetPickUp::OnAssetDoubleClickedFromPicker(const FAssetData & AssetData)
{
	if (UObject * ObjectToEdit = AssetData.GetAsset()) {
		FAssetEditorManager::Get().OpenEditorForAsset(ObjectToEdit);
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE