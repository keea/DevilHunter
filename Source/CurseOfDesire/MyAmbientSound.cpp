// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAmbientSound.h"
#include "MyGameInstance.h"
#include "Engine/World.h"
#include "SingletonObject.h"
#include "Engine/Engine.h"
#include "Components/AudioComponent.h"

AMyAmbientSound::AMyAmbientSound() 
{
	if (GEngine != NULL) 
	{
		UE_LOG(LogTemp, Log, TEXT("GEngine Not NULL"));
		USingletonObject *  instance = Cast < USingletonObject >(GEngine->GameSingleton);

		if (instance != NULL) 
		{
			GetAudioComponent()->SetSound(instance->GetSound(SoundID));		
			UE_LOG(LogTemp, Log, TEXT("Create SoundChange"));
			instance->Get_SoundList()->Fuc_DeleMulti_SoundChange.AddUFunction(this, FName("SoundChange"));

			if(instance->Get_SoundList()->Fuc_DeleMulti_SoundChange.IsBound() == true)
				UE_LOG(LogTemp, Log, TEXT("SoundChange Bound"));
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GEngine NULL"));
	}
}

void AMyAmbientSound::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	USingletonObject *  instance = Cast < USingletonObject >(GEngine->GameSingleton);
	if (instance != NULL)
	{
		UE_LOG(LogTemp, Log, TEXT("SoundChange PostInitializeComponents"));
		GetAudioComponent()->SetSound(instance->GetSound(SoundID));
	}
}

void AMyAmbientSound::SoundChange(TEnumAsByte<ESOUNDS> id)
{
	UE_LOG(LogTemp, Log, TEXT("Start SoundChange!!! Receive"));
	if (id == SoundID)
	{
		UE_LOG(LogTemp, Log, TEXT("Start SoundChange!!! OK"));
		USingletonObject *  instance = Cast < USingletonObject >(GEngine->GameSingleton);
		GetAudioComponent()->SetSound(instance->GetSound(SoundID));
	}
	else 
	{
		UE_LOG(LogTemp, Log, TEXT("Start SoundChange!!! Not ID"));
	}
}

#if WITH_EDITOR

void AMyAmbientSound::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyAmbientSound, SoundID))
	{
		if ( SoundID != ESOUNDS::NONE) {
			USingletonObject *  instance = Cast < USingletonObject >(GEngine->GameSingleton);
			if (GEngine->GameSingleton != NULL)
			{
				UE_LOG(LogTemp, Log, TEXT("instance Sound Not NULL"));
				GetAudioComponent()->SetSound(instance->GetSound(SoundID));
			}
			else 
			{
				UE_LOG(LogTemp, Log, TEXT("instance Sound NULL"));
			}
		}	
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
