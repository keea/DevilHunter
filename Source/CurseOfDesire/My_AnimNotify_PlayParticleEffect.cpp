// Fill out your copyright notice in the Description page of Project Settings.


#include "My_AnimNotify_PlayParticleEffect.h"
#include "MyGameInstance.h"
#include "Engine/World.h"
#include "SingletonObject.h"
#include "Engine/Engine.h"

void UMy_AnimNotify_PlayParticleEffect::EffectChange(TEnumAsByte<EEFFECTS> id)
{
	if (id == EffectID)
	{
		UE_LOG(LogTemp, Log, TEXT("Start SoundChange!!! OK"));
		USingletonObject *  instance = Cast < USingletonObject >(GEngine->GameSingleton);
		PSTemplate = instance->GetEffect(EffectID);
	}
}

#if WITH_EDITOR
void UMy_AnimNotify_PlayParticleEffect::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UMy_AnimNotify_PlayParticleEffect, EffectID))
	{
		USingletonObject *  instance = Cast < USingletonObject >(GEngine->GameSingleton);
		if (GEngine->GameSingleton != NULL)
		{
			UE_LOG(LogTemp, Log, TEXT("instance Sound Not NULL"));
			PSTemplate = instance->GetEffect(EffectID);
		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
