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
		//hp ȸ��
		player->SetHP(player->GetHP() + UpperHp);
	}
	else 
	{
		//Ÿ�̸� ���
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
	//������� ���Ѵٸ� false�� ��ȯ.
	if (!isUsed /*|| GetCount() <= 0*/) 
	{
		//���� ����� �Ұ���(����߱� ������)
		player->UiText->NotPotionCheck();

		UE_LOG(LogTemp, Log, TEXT("Not use hp portion"));
		return false;
	}

	
	isUsed = false;

	//������ ������ ���δ�.
	count -=1;

	// hp������ ��ġ��  6�ʰ� �ִ� ü��(4000)�� 10%��(400��) 1�ʸ��� ȸ��
	CountDownTime = 6;
	FTimerDelegate HpUperTimerDelegate = FTimerDelegate::CreateUObject(this, &UHpPortion::HpRecovery, player);
	//hp�� ���� �ð� ���� ȸ���Ѵ�.
	GetWorld()->GetTimerManager().SetTimer(m_HpUperTimer, HpUperTimerDelegate, 1.0f, true);

	return true;
}

void UHpPortion::PlayerDie()
{
	//Ÿ�̸� ���
	GetWorld()->GetTimerManager().ClearTimer(m_HpUperTimer);
	CountDownTime = 6;
	ResetCoolTime();
}
