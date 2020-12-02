// Fill out your copyright notice in the Description page of Project Settings.


#include "ToxicPlantTrap.h"
#include "MyPlayer.h"
#include "Condition.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

AToxicPlantTrap::AToxicPlantTrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AToxicPlantTrap::BeginPlay()
{
	Super::BeginPlay();
	//�ݸ��� �Լ��� ����
	TrapCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AToxicPlantTrap::OnOverlapBegin);
	TrapCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseTrap::OnOverlapEnd);
	TrapNiagaraEffectComponent->OnSystemFinished.AddDynamic(this, &ABaseTrap::OnTrapNiagaraEffectFinished);
}

void AToxicPlantTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (isOnTrap) 
	{
		AMyPlayer * player = Cast<AMyPlayer>(OtherActor);
		//�ٷ� ���� �ߵ�
		OnActivateTrap(player);
	}
}

void AToxicPlantTrap::OnActivateTrap(AMyPlayer * player)
{
	//���� ���¸� �ο��Ѵ�.
	player->SetCondition(STAT_POSION);
}
