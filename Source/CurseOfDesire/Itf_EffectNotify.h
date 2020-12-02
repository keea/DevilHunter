// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Itf_EffectNotify.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItf_EffectNotify : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CURSEOFDESIRE_API IItf_EffectNotify
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//�÷��̾� ��Ȱ ��
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Effect")
	void Itf_PlayerReviveEffect();

	//�÷��̾� ���� ��
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Effect")
	void Itf_PlayerSttifenEffect();

	//������ ������ ��
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Effect")
	void Itf_PlayerManaburnChar();
};
