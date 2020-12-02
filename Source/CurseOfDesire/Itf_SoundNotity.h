// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundList.h"
#include "UObject/Interface.h"
#include "Itf_SoundNotity.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItf_SoundNotity : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CURSEOFDESIRE_API IItf_SoundNotity
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//플레이어 부활 시
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Sound")
	void Itf_ChangeSound(ESOUNDS sound);
};
