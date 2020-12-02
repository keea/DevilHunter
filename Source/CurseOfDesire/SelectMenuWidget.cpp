// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMenuWidget.h"
#include "Engine.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

USelectMenuWidget::USelectMenuWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{

}

bool USelectMenuWidget::Initialize()
{
	Super::Initialize();
	if (MostionOne != nullptr)
	{
		MostionOne->OnClicked.AddDynamic(this, &USelectMenuWidget::OnClickedCharacterone);
	}
	if (MostionTwo != nullptr)
	{
		MostionTwo->OnClicked.AddDynamic(this, &USelectMenuWidget::OnClickedCharactertwo);
	}
	if (MostionThree != nullptr)
	{
		MostionThree->OnClicked.AddDynamic(this, &USelectMenuWidget::OnClickedCharacterthree);
	}
	if (MostionFour != nullptr)
	{
		MostionFour->OnClicked.AddDynamic(this, &USelectMenuWidget::OnClickedCharacterfour);
	}
	return true;
}

void USelectMenuWidget::OnClickedCharacterone()
{
	if (selectmotion != false)
	{
		PlayAnimation(SelectOnAnimation, 0.F, 1, EUMGSequencePlayMode::Forward, 0.5f);
		selectmotion = false;
	}
}

void USelectMenuWidget::OnClickedCharactertwo()
{
	if (selectmotion != false)
	{
		PlayAnimation(TwoSelectOnAnimation, 0.F, 1, EUMGSequencePlayMode::Forward, 0.5f);
		selectmotion = false;
	}
}

void USelectMenuWidget::OnClickedCharacterthree()
{
	if (selectmotion != false)
	{
		PlayAnimation(ThreeSelectOnAnimation, 0.F, 1, EUMGSequencePlayMode::Forward, 0.5f);
		selectmotion = false;
	}
}

void USelectMenuWidget::OnClickedCharacterfour()
{
	if (selectmotion != false)
	{
		PlayAnimation(FourSelectAnimation, 0.F, 1, EUMGSequencePlayMode::Forward, 0.5f);
		selectmotion = false;
	}
}

void USelectMenuWidget::NextLevel()
{
	UWorld* World = GetWorld();
	FString NextMap = FString::Printf(TEXT("/Game/DevilHunter/Stage/StartPlace/StartPlace"));
	GetWorld()->SeamlessTravel(NextMap);
	RemoveFromParent();
}

UWidgetAnimation * USelectMenuWidget::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnimation = AnimationsMap.Find(AnimationName);
	if (WidgetAnimation)
	{
		return *WidgetAnimation;
	}
	return nullptr;
}

void USelectMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StoreWidgetAnimations();

	SelectOnAnimation = GetAnimationByName(TEXT("SelectOnAnimation"));
	NoSelectAnimation = GetAnimationByName(TEXT("NoSelectAnimation"));
	TwoSelectOnAnimation = GetAnimationByName(TEXT("TwoSelectAnimation"));
	TwoNoSelectAnimation = GetAnimationByName(TEXT("TwoNoSelectAnimation"));
	ThreeSelectOnAnimation = GetAnimationByName(TEXT("ThreeOn"));
	ThreeNoSelectAnimation = GetAnimationByName(TEXT("ThreeNo"));
	FourSelectAnimation = GetAnimationByName(TEXT("FourOn"));
	FourNoSelectAnimation = GetAnimationByName(TEXT("FourNo"));
}

void USelectMenuWidget::StoreWidgetAnimations()
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

