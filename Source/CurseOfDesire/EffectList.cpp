// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectList.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"

UEffectList::UEffectList()
{
	UE_LOG(LogTemp, Log, TEXT("UEffectList::UEffectList()"));
	for (int i = 1; i < (BYTE)EEFFECTS::END; i++) {
		EffectList.Add((TEnumAsByte<EEFFECTS>)i, NULL);
	}
}

UParticleSystem * UEffectList::GetEffect(TEnumAsByte<EEFFECTS> effectIdx)
{
	if (EffectList.Find(effectIdx) == NULL)
		return NULL;
	else
		return EffectList[effectIdx];
}
