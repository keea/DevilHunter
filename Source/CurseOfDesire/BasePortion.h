// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "BasePortion.generated.h"


/**
 *
 */
UCLASS()
class CURSEOFDESIRE_API UBasePortion : public UObject
{
	GENERATED_BODY()

private:
	

public:
	//포션 갯수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portion)
	int count;

	//포션이 비어 있는가?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portion)
	bool isEmpty;

	//사용 가능한 상태인가?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portion)
	bool isUsed;

	//쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portion)
	float coolTime;


protected:
	UPROPERTY()
	FTimerHandle m_CoolTimeTimer;

public:
	UBasePortion();

	//물약 갯수 반환
	UFUNCTION()
	virtual int GetCount();

	//성공 실패 반환.
	UFUNCTION()
	virtual bool Execute(class AMyPlayer * player);

	UFUNCTION()
	void ResetCoolTime();

	//플레이어 사망시 처리.
	UFUNCTION()
	virtual void PlayerDie() {};
};
