// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrap.h"
#include "TestConditionTrap.generated.h"

/**
 * 
 */
UCLASS()
class TRAP_API ATestConditionTrap : public ABaseTrap
{
	GENERATED_BODY()
public:
	ATestConditionTrap();

protected:
	virtual void BeginPlay() override;

public:
	//Ʈ�� Ʈ���� ����(�浹 ���� ��)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//���� �ߵ� �Լ�
	virtual void OnActivateTrap(class AMyPlayer * player);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test)
		bool isManaBurn = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test)
		bool isPush = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test)
		bool isStun = false;

private:
	UPROPERTY()
	FVector HitNormal;
};
