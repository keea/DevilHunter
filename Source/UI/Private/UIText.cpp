// Fill out your copyright notice in the Description page of Project Settings.


#include "UIText.h"
#include "MyPlayer.h"
#include "TimerManager.h"

UUIText::UUIText()
{
}

void UUIText::SetInit(AMyPlayer * player)
{
	this->player = player;
}

FText UUIText::GetMPIntText()
{
	FString MPS = FString::FromInt(player->CharMp);
	FString FULLMPS = FString::FromInt(player->CharMaxMp);
	FString MPHUD = MPS + FString(TEXT("/")) + FULLMPS;
	FText MPText = FText::FromString(MPHUD);
	return MPText;
}

FText UUIText::GetHPIntText()
{
	if (player->GetHP() <= 0)
	{
		FString HPS = FString::FromInt(0);
		FString FULLHPS = FString::FromInt(player->GetMaxHP());
		FString HPHUD = HPS + FString(TEXT("/")) + FULLHPS;
		FText HPText = FText::FromString(HPHUD);
		return HPText;
	}
	else
	{
		FString HPS = FString::FromInt(player->GetHP());
		FString FULLHPS = FString::FromInt(player->GetMaxHP());
		FString HPHUD = HPS + FString(TEXT("/")) + FULLHPS;
		FText HPText = FText::FromString(HPHUD);
		return HPText;
	}
}

void UUIText::ExecuteHpPortionTimer(float coolTime)
{
	HPPotionProgress.Broadcast();
}

void UUIText::ExecuteMpPortionTimer(float coolTime)
{
	MPPotionProgress.Broadcast();
}

void UUIText::SkillChecker(int type, FTimerHandle timerHander, float Cooldown)
{
	switch (type)
	{
	case 0:
		Skill1Progress.Broadcast();
		break;
	case 1:
		Skill2Progress.Broadcast();
		break;
	case 2:
		Skill3Progress.Broadcast();
		break;
	case 3:
		Skill4Progress.Broadcast();
		break;
	case 4:
		AwaikingProgress.Broadcast();
		break;
	}
}

void UUIText::NotSkillCheck()
{
	NotSkillProgress.Broadcast();
}

void UUIText::NotPotionCheck()
{
	NotPotionProgress.Broadcast();
}

void UUIText::ConditionChecker(int Conditonnum)
{
	switch (Conditonnum)
	{
	case 1:
		PoisonProgress.Broadcast();
		break;
	case 2:
		FaintProgress.Broadcast();
		break;
	case 3:
		ManaburnProgress.Broadcast();
		break;
	case 4:
		StiffnessProgress.Broadcast();
	}
}

void UUIText::HPCheck()
{
	HpProgress.Broadcast();
}

void UUIText::MPCheck()
{
	MpProgress.Broadcast();
}

void UUIText::DashCheck()
{
	DashProgress.Broadcast();
}

void UUIText::DeadCheck()
{
	DeadProgress.Broadcast();
}

void UUIText::MBFlowerCheck()
{
	FlowerProgress.Broadcast();
}

int UUIText::GetDeadCount()
{
	return deadcount;
}

void UUIText::MinusDeadCount()
{
	deadcount -= 1;
}

void UUIText::FBBerserk()
{
	BerserkProgress.Broadcast();
}

void UUIText::UnlockAwake()
{
	UnlockAwaikProgress.Broadcast();
}

void UUIText::CreateCombo()
{
	ComboProgress.Broadcast();
}

void UUIText::MonHp()
{
	MonsterHpProgress.Broadcast();
}

void UUIText::FBTimeOutCheck()
{
	FBTimeOut = true;
}

void UUIText::Pvasion()
{
	evasionProgress.Broadcast();
}
