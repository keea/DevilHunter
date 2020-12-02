// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SceneOutlinerFwd.h"
#include "DeclarativeSyntaxSupport.h" //include for Args

/**
 * 
 */
class WORLDMONSTERMODULE_API SMySceneOutliner : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMySceneOutliner)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void OnSceneOutlinerItemClicked(TSharedRef<SceneOutliner::ITreeItem> InItem);

protected:
	TSharedPtr< class IDetailsView> DetailsView;
	TSharedPtr< class ISceneOutliner> SceneOutliner;
};
