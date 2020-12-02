// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePortion.h"
#include "MpPortion.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API UMpPortion : public UBasePortion
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	FTimerHandle m_MpUperTimer;

private:
	UPROPERTY()
	int CountDownTime;

	UFUNCTION()
	void MpRecovery(class AMyPlayer * player);

public:
	UMpPortion();
	virtual bool Execute(class AMyPlayer * player);

	//플레이어 죽음 처리
	virtual void PlayerDie();
};
