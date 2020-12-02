// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Loading;

public:
	ULoadingWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void LoadingWidgetAnimation();

	UFUNCTION()
		void ViewLoading();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

private:
	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* LoadingAnimation;
	
};
