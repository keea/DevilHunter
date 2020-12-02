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
	//트랩 트리거 설정(충돌 했을 때)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//함정 발동 함수
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
