// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingWidget.h"
#include "Engine.h"
#include "Components/ProgressBar.h"

ULoadingWidget::ULoadingWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
}

void ULoadingWidget::ViewLoading()
{
	PlayAnimation(LoadingAnimation, 0.F, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

UWidgetAnimation * ULoadingWidget::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnimation = AnimationsMap.Find(AnimationName);
	if (WidgetAnimation)
	{
		return *WidgetAnimation;
	}
	return nullptr;
}

void ULoadingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadingWidgetAnimation();

	LoadingAnimation = GetAnimationByName(TEXT("Progress"));

	ViewLoading();
}

void ULoadingWidget::LoadingWidgetAnimation()
{
	AnimationsMap.Empty();

	UProperty* Prop = GetClass()->PropertyLink;

	while (Prop != nullptr)
	{
		if (Prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);

			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* WidgetAnim = Cast<UWidgetAnimation>(Obj);

				if (WidgetAnim != nullptr && WidgetAnim->MovieScene != nullptr)
				{
					FName AnimName = WidgetAnim->MovieScene->GetFName();
					AnimationsMap.Add(AnimName, WidgetAnim);
				}
			}
		}
		Prop = Prop->PropertyLinkNext;
	}
}

