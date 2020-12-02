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
	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portion)
	int count;

	//������ ��� �ִ°�?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portion)
	bool isEmpty;

	//��� ������ �����ΰ�?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portion)
	bool isUsed;

	//��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portion)
	float coolTime;


protected:
	UPROPERTY()
	FTimerHandle m_CoolTimeTimer;

public:
	UBasePortion();

	//���� ���� ��ȯ
	UFUNCTION()
	virtual int GetCount();

	//���� ���� ��ȯ.
	UFUNCTION()
	virtual bool Execute(class AMyPlayer * player);

	UFUNCTION()
	void ResetCoolTime();

	//�÷��̾� ����� ó��.
	UFUNCTION()
	virtual void PlayerDie() {};
};
