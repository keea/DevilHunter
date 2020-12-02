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
	//AssetPicker ��� ���� �̺�Ʈ �ݹ�.
	void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);

	//AssetPicker ��� ���� Ŭ�� �̺�Ʈ �ݹ�.
	void OnAssetDoubleClickedFromPicker(const struct FAssetData& AssetData);

protected:
	TSharedPtr< class IDetailsView > DetailsView;
};
