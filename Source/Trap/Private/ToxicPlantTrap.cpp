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
	//콜리전 함수와 연결
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
		//바로 함정 발동
		OnActivateTrap(player);
	}
}

void AToxicPlantTrap::OnActivateTrap(AMyPlayer * player)
{
	//독성 상태를 부여한다.
	player->SetCondition(STAT_POSION);
}
