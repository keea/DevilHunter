// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundList.h"
#include "EffectList.h"
#include "SingletonObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CURSEOFDESIRE_API USingletonObject : public UObject
{
	GENERATED_BODY()
private:
	USingletonObject();
public:
	static  USingletonObject *  GetInstance();

#pragma region 사운드
public:
	//사운드 리스트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		TSubclassOf<class USoundList> SoundList;

	//사운드 가져오기
	UFUNCTION(BlueprintPure, Category = Sound)
		class USoundCue * GetSound(TEnumAsByte<ESOUNDS> soundIdx);

	USoundList * Get_SoundList();
#pragma endregion 사운드

#pragma region 이펙트
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	TSubclassOf<class UEffectList> EffectList;

	//이펙트 가져오기
	UFUNCTION(BlueprintPure, Category = Sound)
	class UParticleSystem * GetEffect(TEnumAsByte<EEFFECTS> soundIdx);
#pragma endregion 이펙트
};
