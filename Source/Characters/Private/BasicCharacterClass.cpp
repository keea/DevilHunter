// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacterClass.h"

// Sets default values
ABasicCharacterClass::ABasicCharacterClass()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicCharacterClass::BeginPlay()
{
	Super::BeginPlay();

	//처음 시작 시 현재체력을 최대체력으로 변환한다.
	HP = MaxHP;
}

// Called every frame
void ABasicCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ABasicCharacterClass::GetATK()
{
	return ATK;
}

float ABasicCharacterClass::GetMaxHP() const
{
	return MaxHP;
}

float ABasicCharacterClass::GetHP() const
{
	return HP;
}

void ABasicCharacterClass::SetATK(int atk)
{
	ATK = atk;
}

void ABasicCharacterClass::SetMaxHP(float maxHp)
{
	MaxHP = maxHp;
}

void ABasicCharacterClass::SetHP(int hp)
{
	//hp가 MaxHP 넘지 않도록 막기.
	if (hp > MaxHP) 
	{
		HP = MaxHP;
		return;
	}
	HP = hp;
}

void ABasicCharacterClass::CMDSetHP(int _hp)
{
	MaxHP = _hp; //max hp를 변경한다.
	HP = _hp; //hp를 변경한다.
}

void ABasicCharacterClass::CMDSetATK(int _atk)
{
	ATK = _atk; //공격력을 변경한다.
}

