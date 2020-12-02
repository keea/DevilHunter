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
		//mp ȸ��
		player->SetMP(player->GetMp() + UpperMp);
	}
	else {
		//Ÿ�̸� ���
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
	//������� ���Ѵٸ� false�� ��ȯ.
	if (!isUsed /*|| GetCount() <= 0*/) {
		//���� ����� �Ұ���(����߱� ������)
		player->UiText->NotPotionCheck();

		UE_LOG(LogTemp, Log, TEXT("Not use mp portion"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("use mp portion"));


	isUsed = false;

	//������ ������ ���δ�.
	count -= 1;

	// mp������ ��ġ��  6�ʰ� �ִ� ü��(4000)�� 10%��(400��) 1�ʸ��� ȸ��
	CountDownTime = 6;
	FTimerDelegate MpUperTimerDelegate = FTimerDelegate::CreateUObject(this, &UMpPortion::MpRecovery, player);
	//mp�� ���� �ð� ���� ȸ���Ѵ�.
	GetWorld()->GetTimerManager().SetTimer(m_MpUperTimer, MpUperTimerDelegate, 1.0f, true);

	return true;
}

void UMpPortion::PlayerDie()
{
	//Ÿ�̸� ���
	GetWorld()->GetTimerManager().ClearTimer(m_MpUperTimer);
	CountDownTime = 6;
	ResetCoolTime();
}
