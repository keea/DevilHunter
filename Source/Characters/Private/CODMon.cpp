// Fill out your copyright notice in the Description page of Project Settings.

#include "CODMon.h"
#include "Engine.h"
#include "CurseOfDesire.h"
//#include "MyAnimInstance.h"

// Sets default values
ACODMon::ACODMon()
{
}

// Called when the game starts or when spawned
void ACODMon::BeginPlay()
{
	
}

// Called every frame
void ACODMon::Tick(float DeltaTime)
{
	//PlayAnimMontage(AnimMontages[IDLE], 1.f, FName("Default"));
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACODMon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACODMon::Tracking()
{//PlayAnimMontage(MeleeAttackMontage, -1.f, FName("Default")); 
	//m_isAttackAnim = false;
	
}

void ACODMon::HPRecover()
{
	
}

void ACODMon::MonsterMove()
{
	
}

void ACODMon::Idle()
{
	
}

void ACODMon::Trigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}

bool ACODMon::GetIsPlayerDie()
{
	return false;
}

bool ACODMon::GetIsMonsterDie()
{
	if (GetHP() <= 0)
		return true;

	else
		return false;
}

float ACODMon::GetIsMonSpeed()
{
	return real_Speed;
}

void ACODMon::SetIsMonSpeed(float Speed)
{
	real_Speed = Speed;
}

bool ACODMon::GetIsFindChar()
{
	return findChar;
}

void ACODMon::SetIsFindChar(bool findchar)
{
	findChar = findchar;
}

bool ACODMon::GetIsAttaken()
{
	return attakenMon;
}