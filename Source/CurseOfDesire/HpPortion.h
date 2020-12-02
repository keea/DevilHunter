// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePortion.h"
#include "HpPortion.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API UHpPortion : public UBasePortion
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	FTimerHandle m_HpUperTimer;

private:
	UFUNCTION()
	void HpRecovery(class AMyPlayer * player);

public:
	UPROPERTY()
	int CountDownTime;

	UHpPortion();

	//성공 실패 반환.
	virtual bool Execute(class AMyPlayer * player);
	//플레이어 죽음 처리
	virtual void PlayerDie();
};
