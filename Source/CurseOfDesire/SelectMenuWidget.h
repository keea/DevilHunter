// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API USelectMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		class UButton* MostionOne;

	UPROPERTY(meta = (BindWidget))
		class UButton* MostionTwo;

	UPROPERTY(meta = (BindWidget))
		class UButton* MostionThree;

	UPROPERTY(meta = (BindWidget))
		class UButton* MostionFour;

	virtual bool Initialize() override;

public:
	USelectMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void StoreWidgetAnimations();

	UFUNCTION()
		void OnClickedCharacterone();

	UFUNCTION()
		void OnClickedCharactertwo();

	UFUNCTION()
		void OnClickedCharacterthree();

	UFUNCTION()
		void OnClickedCharacterfour();

	UFUNCTION(BlueprintCallable)
		void NextLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool selectmotion = true;


	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

private:
	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* SelectOnAnimation;
	UWidgetAnimation* NoSelectAnimation;
	UWidgetAnimation* TwoSelectOnAnimation;
	UWidgetAnimation* TwoNoSelectAnimation;
	UWidgetAnimation* ThreeSelectOnAnimation;
	UWidgetAnimation* ThreeNoSelectAnimation;
	UWidgetAnimation* FourSelectAnimation;
	UWidgetAnimation* FourNoSelectAnimation;
};
