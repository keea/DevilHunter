// Fill out your copyright notice in the Description page of Project Settings.


#include "MpPortion.h"
#include "MyPlayer.h"
#include "TimerManager.h"
#include "UIText.h"

void UMpPortion::MpRecovery(AMyPlayer * player)
{
	UE_LOG(LogTemp, Log, TEXT("MpRecovery"));
	if (CountDownTime > 1) {
		CountDownTime--;

		UE_LOG(LogTemp, Log, TEXT("MP UP"));
		int UpperMp = player->CharMaxMp * 0.1f;
		//mp 회복
		player->SetMP(player->GetMp() + UpperMp);
	}
	else {
		//타이머 취소
		GetWorld()->GetTimerManager().ClearTimer(m_MpUperTimer);
		CountDownTime = 6;
		GetWorld()->GetTimerManager().SetTimer(m_CoolTimeTimer, this, &UBasePortion::ResetCoolTime, coolTime, false);

		player->UiText->ExecuteMpPortionTimer(coolTime);
	}
}

UMpPortion::UMpPortion()
{
	isUsed = true;
	CountDownTime = 6;
	coolTime = 10.f;
}

bool UMpPortion::Execute(AMyPlayer * player)
{
	//사용하지 못한다면 false를 반환.
	if (!isUsed /*|| GetCount() <= 0*/) {
		//포션 사용이 불가능(사용했기 때문에)
		player->UiText->NotPotionCheck();

		UE_LOG(LogTemp, Log, TEXT("Not use mp portion"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("use mp portion"));


	isUsed = false;

	//포션의 갯수를 줄인다.
	count -= 1;

	// mp포션의 수치도  6초간 최대 체력(4000)의 10%씩(400씩) 1초마다 회복
	CountDownTime = 6;
	FTimerDelegate MpUperTimerDelegate = FTimerDelegate::CreateUObject(this, &UMpPortion::MpRecovery, player);
	//mp를 일정 시간 동안 회복한다.
	GetWorld()->GetTimerManager().SetTimer(m_MpUperTimer, MpUperTimerDelegate, 1.0f, true);

	return true;
}

void UMpPortion::PlayerDie()
{
	//타이머 취소
	GetWorld()->GetTimerManager().ClearTimer(m_MpUperTimer);
	CountDownTime = 6;
	ResetCoolTime();
}
