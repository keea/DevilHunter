// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition.h"
#include "MyPlayer.h"
#include "UIText.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCondition::PosionAdvanceTimer(AMyPlayer * player)
{
	//독으로 감소할 HP양 초기화(전체 HP의 5퍼센트)
	float DiminishHP = player->GetMaxHP() * 0.05f;

	PosionCountdownTime--;
	player->TakePlayerDamage(DiminishHP, false);
	if (PosionCountdownTime < 1) {
		GetWorld()->GetTimerManager().ClearTimer(PosionCountdownTimerHandle);
		PosionCountdownHasFinished();
	}
}

void UCondition::PosionCountdownHasFinished()
{
	//초기화
	PosionCountdownTime = 0;

	PlayerStat &= !(STAT_POSION);
}

void UCondition::ExecuteManaBurn(AMyPlayer * player)
{
	if (player->GetClass()->ImplementsInterface(UItf_EffectNotify::StaticClass()) == true) {
		//마나번 상태임을 알린다.
		IItf_EffectNotify::Execute_Itf_PlayerManaburnChar(player);
	}

	//일단 플레이어의 MP를 0으로 만든다.
	player->SetMP(player->GetMaxHP() * 0.3f);

	//초기화
	PlayerStat &= !(STAT_MANABURN);
}

void UCondition::ExecuteManaPercentBurn(AMyPlayer * player, float percent)
{
	if (player->GetClass()->ImplementsInterface(UItf_EffectNotify::StaticClass()) == true) {
		//마나번 상태임을 알린다.
		IItf_EffectNotify::Execute_Itf_PlayerManaburnChar(player);
	}

	//전체 값.
	int currentMP = player->GetMp();
	//바뀔 마나.
	float changeMP = currentMP - ((currentMP * percent) * 0.001f);

	//마나를 변경시킨다.
	player->SetMP(changeMP);

	//초기화
	PlayerStat &= !(STAT_MANABURN);
}

void UCondition::KnockbackEnd(AMyPlayer * player)
{
	player->GetCharacterMovement()->StopMovementImmediately();
	player->GetCharacterMovement()->BrakingFrictionFactor = 2.f;

	//데미지 애니메이션 재생 취소
	player->m_bPlayTakeDamageAnimation = false;

	//초기화
	PlayerStat &= !(STAT_PUSH);
}

UCondition::UCondition()
{
	InitCondition();
}

void UCondition::AddCondition(int condition, AMyPlayer * player)
{
	//상태 이상도 살아 있을 때만!!!
	if (player->CurrentState != STATE_TYPE::STATE_DEFAULE)
		return;

	//상태 추가
	PlayerStat |= condition;

	//상태 실행(일단 if문으로 작업한다. 추후에 수정할 방안 생각)
	if (PlayerStat & STAT_POSION) //중독
	{
		//상태이상 알림.
		player->UiText->ConditionChecker(1);
		//5초 동안
		PosionCountdownTime += 5;
		FTimerDelegate PosionCountdownDelegate = FTimerDelegate::CreateUObject(this, &UCondition::PosionAdvanceTimer, player);
		GetWorld()->GetTimerManager().SetTimer(PosionCountdownTimerHandle, PosionCountdownDelegate, 1.0f, true);
	}
	else if (PlayerStat & STAT_MANABURN) //마나번
	{
		//상태이상 알림.
		player->UiText->ConditionChecker(3);
		ExecuteManaBurn(player);
	}

	else if (PlayerStat & STAT_STUN) //스턴
	{
		//스턴 이펙트를 실행한다.
		if (player->GetClass()->ImplementsInterface(UItf_EffectNotify::StaticClass()) == true) {
			IItf_EffectNotify::Execute_Itf_PlayerSttifenEffect(player);
		}

		//상태이상 알림.
		player->UiText->ConditionChecker(2);

		//스턴 애니메이션 재생
		player->PlayStunAnimation();

		//피격 애니메이션 재생 상태를 true로 바꾼다.
		player->m_bPlayTakeDamageAnimation = true;

		//player->UiText->OnTestDelegate.Broadcast();
	}
}

void UCondition::InitCondition()
{
	//상태 초기화
	PlayerStat &= STAT_NONE;

	//초기화
	PosionCountdownTime = 0;
}

void UCondition::DeleteCondition(int condition)
{
	PlayerStat &= condition;
}

bool UCondition::IsCheckCondition(int condition)
{
	return PlayerStat & condition;
}
