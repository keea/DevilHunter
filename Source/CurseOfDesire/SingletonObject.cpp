// Fill out your copyright notice in the Description page of Project Settings.


#include "SingletonObject.h"
#include "Engine/Engine.h"

USingletonObject::USingletonObject()
{

}

USingletonObject *  USingletonObject::GetInstance()
{
	if (GEngine)
	{
		USingletonObject *  instance = Cast < USingletonObject >(GEngine->GameSingleton);
		return  instance;
	}
	return  nullptr;
}

USoundCue * USingletonObject::GetSound(TEnumAsByte<ESOUNDS> soundIdx)
{
	if (SoundList != NULL) {
		USoundList * soundList = SoundList.GetDefaultObject();
		UE_LOG(LogTemp, Log, TEXT("GetSound"));

		if (soundList->GetSound(soundIdx) != NULL) {
			UE_LOG(LogTemp, Log, TEXT("Sound Name :: %s"), *soundList->GetSound(soundIdx)->GetName());
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Sound NULL"));
		}

		return soundList->GetSound(soundIdx);
	}
	return NULL;
}

USoundList * USingletonObject::Get_SoundList()
{
	USoundList * soundList = SoundList.GetDefaultObject();
	return soundList;
}

UParticleSystem * USingletonObject::GetEffect(TEnumAsByte<EEFFECTS> effectIdx)
{
	if (EffectList != NULL)
	{
		UEffectList * effectList = EffectList.GetDefaultObject();
		return effectList->GetEffect(effectIdx);
	}

	return NULL;
}
