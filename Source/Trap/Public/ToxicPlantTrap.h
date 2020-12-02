// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrap.h"
#include "ToxicPlantTrap.generated.h"

/**
 * 
 */
UCLASS()
class TRAP_API AToxicPlantTrap : public ABaseTrap
{
	GENERATED_BODY()
	
public:
	AToxicPlantTrap();

protected:
	virtual void BeginPlay() override;

public:
	//Ʈ�� Ʈ���� ����(�浹 ���� ��)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//���� �ߵ� �Լ�
	virtual void OnActivateTrap(class AMyPlayer * player);
};
