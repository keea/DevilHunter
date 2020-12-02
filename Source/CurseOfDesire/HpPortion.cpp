// Fill out your copyright notice in the Description page of Project Settings.


#include "HpPortion.h"
#include "MyPlayer.h"
#include "TimerManager.h"
#include "UIText.h"


void UHpPortion::HpRecovery(AMyPlayer * player)
{
	UE_LOG(LogTemp, Log, TEXT("HpRecovery"));
	if (CountDownTime > 1) 
	{
		CountDownTime--;
		
		UE_LOG(LogTemp, Log, TEXT("HP UP"));
		int UpperHp = player->GetMaxHP() * 0.1f;
		//hp 회복
		player->SetHP(player->GetHP() + UpperHp);
	}
	else 
	{
		//타이머 취소
		GetWorld()->GetTimerManager().ClearTimer(m_HpUperTimer);
		CountDownTime = 6;
		GetWorld()->GetTimerManager().SetTimer(m_CoolTimeTimer, this, &UBasePortion::ResetCoolTime, coolTime, false);

		player->UiText->ExecuteHpPortionTimer(coolTime);
	}
}

UHpPortion::UHpPortion()  
{
	isUsed = true;
	CountDownTime = 6;
	coolTime = 15.f;
}

bool UHpPortion::Execute(AMyPlayer * player)
{
	//사용하지 못한다면 false를 반환.
	if (!isUsed /*|| GetCount() <= 0*/) 
	{
		//포션 사용이 불가능(사용했기 때문에)
		player->UiText->NotPotionCheck();

		UE_LOG(LogTemp, Log, TEXT("Not use hp portion"));
		return false;
	}

	
	isUsed = false;

	//포션의 갯수를 줄인다.
	count -=1;

	// hp포션의 수치도  6초간 최대 체력(4000)의 10%씩(400씩) 1초마다 회복
	CountDownTime = 6;
	FTimerDelegate HpUperTimerDelegate = FTimerDelegate::CreateUObject(this, &UHpPortion::HpRecovery, player);
	//hp를 일정 시간 동안 회복한다.
	GetWorld()->GetTimerManager().SetTimer(m_HpUperTimer, HpUperTimerDelegate, 1.0f, true);

	return true;
}

void UHpPortion::PlayerDie()
{
	//타이머 취소
	GetWorld()->GetTimerManager().ClearTimer(m_HpUperTimer);
	CountDownTime = 6;
	ResetCoolTime();
}
