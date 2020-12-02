// Fill out your copyright notice in the Description page of Project Settings.

#include "MySkillUltimate.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"
#include "Engine/World.h"
#include "TimerManager.h"

AMySkillUltimate::AMySkillUltimate() 
{

}

void AMySkillUltimate::BeginPlay()
{
	Super::BeginPlay();
}

void AMySkillUltimate::Execute() 
{
	UE_LOG(LogTemp, Log, TEXT("Invincibility ON"));
	//캐릭터 정보 가져오기
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//캐릭터 형변환
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	//각성 상태로 돌입한다.
	player->StartUltimate(UltimateTime);
}
