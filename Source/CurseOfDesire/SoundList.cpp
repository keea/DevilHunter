// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundList.h"

USoundList::USoundList()
{
	UE_LOG(LogTemp, Log, TEXT("UEffectList::UEffectList()"));
	for (int i = 1; i < (BYTE)ESOUNDS::END; i++) {
		SoundList.Add((TEnumAsByte<ESOUNDS>)i, NULL);
	}
}

USoundCue * USoundList::GetSound(TEnumAsByte<ESOUNDS> soundIdx)
{
	if (SoundList.Find(soundIdx) == NULL)
		return NULL;
	else
		return SoundList[soundIdx];
}

#if WITH_EDITOR
//사운드 값이 바뀌었을 때...
void USoundList::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(USoundList, SoundList))
	{
		UE_LOG(LogTemp, Log, TEXT("Start SoundChange!!! Property"));
		for (auto & Elem : SoundList) 
		{
			if (BeforeSoundList.Find(Elem.Key) == NULL)
			{
				if (Fuc_DeleMulti_SoundChange.IsBound() == true) {
					UE_LOG(LogTemp, Log, TEXT("Start SoundChange!!! Send"));
					Fuc_DeleMulti_SoundChange.Broadcast(Elem.Key);
				}
				break;
			}
			else 
			{
				if (SoundList[Elem.Key] != BeforeSoundList[Elem.Key]) 
				{
					if (Fuc_DeleMulti_SoundChange.IsBound() == true) {
						UE_LOG(LogTemp, Log, TEXT("SoundList[Elem.Key] != BeforeSoundList[Elem.Key]Start SoundChange!!! Send"));
						Fuc_DeleMulti_SoundChange.Broadcast(Elem.Key);
					}
					break;
				}
				else 
				{
					UE_LOG(LogTemp, Log, TEXT("Start SoundChange!!! Error"));
				}
			}
		}

		BeforeSoundList.Empty();
		BeforeSoundList = SoundList;
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
