// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Itf_SoundNotity.h"
#include "Sound/AmbientSound.h"
#include "SoundList.h"
#include "MyAmbientSound.generated.h"
/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API AMyAmbientSound : public AAmbientSound
{
	GENERATED_BODY()

public:
	AMyAmbientSound();

	//컴포넌트가 초기화 되었을 때
	virtual void PostInitializeComponents() override;

	//사운드 아이디 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = sound, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ESOUNDS> SoundID;

	UFUNCTION()
	void SoundChange(TEnumAsByte<ESOUNDS> id);

#if WITH_EDITOR
	//프로퍼티 변경될 때 마다 사운드 값 변경
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
