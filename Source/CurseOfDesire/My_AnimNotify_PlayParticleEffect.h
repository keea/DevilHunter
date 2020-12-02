// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlayParticleEffect.h"
#include "EffectList.h"
#include "My_AnimNotify_PlayParticleEffect.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API UMy_AnimNotify_PlayParticleEffect : public UAnimNotify_PlayParticleEffect
{
	GENERATED_BODY()
public:
	//이펙트 아이디 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = sound, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EEFFECTS> EffectID;

	UFUNCTION()
	void EffectChange(TEnumAsByte<EEFFECTS> id);

#if WITH_EDITOR
	//프로퍼티 변경될 때 마다 이펙트 값 변경
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
