// Fill out your copyright notice in the Description page of Project Settings.


#include "TestConditionTrap.h"
#include "Components/BoxComponent.h"
#include "MyPlayer.h"
#include "Condition.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

ATestConditionTrap::ATestConditionTrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATestConditionTrap::BeginPlay()
{
	Super::BeginPlay();

	//�ݸ��� �Լ��� ����
	TrapCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATestConditionTrap::OnOverlapBegin);
	TrapCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseTrap::OnOverlapEnd);

	HitNormal = FVector::ZeroVector;
}

void ATestConditionTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!isOnTrap) {
		Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		if (isOnTrap)
		{
			AMyPlayer * player = Cast<AMyPlayer>(OtherActor);

			if (isPush) {
				//��� ���� �ް�...
				HitNormal = SweepResult.ImpactNormal;
			}

			//�ٷ� ���� �ߵ�
			OnActivateTrap(player);
		}
	}
}

void ATestConditionTrap::OnActivateTrap(AMyPlayer * player)
{
	if (isManaBurn) {
		player->SetCondition<float>(STAT_MANABURN, 30.0f);
	}
	else if (isPush) {
		player->SetCondition<FVector>(STAT_PUSH, HitNormal);
	}
	else if (isStun) {
		player->SetCondition(STAT_STUN);
	}
}
