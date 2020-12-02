// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h" //include for Args

/**
 * 
 */
class MONSTERPLACEMENTTOOL_API SMyAssetPickUpTest : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyAssetPickUpTest)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private :
	//AssetPicker 어셋 선택 이벤트 콜백.
	void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);

	//AssetPicker 어셋 더블 클릭 이벤트 콜백.
	void OnAssetDoubleClickedFromPicker(const struct FAssetData& AssetData);

protected:
	TSharedPtr< class IDetailsView > DetailsView;
};
