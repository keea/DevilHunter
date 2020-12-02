// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayer.h"
#include "UIText.h"
#include "Condition.generated.h"

/**
 * 캐릭터 상태이상 관련
 */
 //기본
#define STAT_NONE		0x00000000
//중독
#define STAT_POSION		0x00000001
//마나번
#define STAT_MANABURN	0x00000002
//경직 : 몸이 뒤로 밀려나며, 경직이 유지되는 동안 행동불능 상태가 된다.
#define STAT_PUSH		0x00000004
//기절(스턴)
#define STAT_STUN		0x00000008

UCLASS()
class CHARACTERS_API UCondition : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
		int PlayerStat;

private:
	//중독 상태에 관한 설정.
	UPROPERTY()
		int PosionCountdownTime;

	UPROPERTY()
		FTimerHandle PosionCountdownTimerHandle;

	//넉백 종료 타임 핸들러
	UPROPERTY()
		FTimerHandle KnockbackEndTimerHandle;

	//중독상태 재생
	UFUNCTION()
		void PosionAdvanceTimer(class AMyPlayer * player);

	//카운트 다운 종료.
	UFUNCTION()
		void PosionCountdownHasFinished();

	//마나 번 실행.
	UFUNCTION()
		void ExecuteManaBurn(class AMyPlayer * player);

	//마나 번 실행.
	UFUNCTION()
		void ExecuteManaPercentBurn(class AMyPlayer * player, float percent);

	//넉백 종료 함수
	UFUNCTION()
		void KnockbackEnd(class AMyPlayer * player);

public:
	UCondition();

	UFUNCTION()
	void AddCondition(int condition, class AMyPlayer * player);

	template<typename T>
	void AddCondition(int condition, AMyPlayer * player, T value);

	//상태 초기화
	UFUNCTION()
		void InitCondition();

	//상태 이상 제거
	UFUNCTION()
		void DeleteCondition(int condition);

	//상태이상 체크
	UFUNCTION()
		bool IsCheckCondition(int condition);
};

template<typename T>
inline void UCondition::AddCondition(int condition, AMyPlayer * player, T value)
{
}

template<>
inline void UCondition::AddCondition<FVector>(int condition, AMyPlayer * player, FVector value) {
	//상태 추가
	PlayerStat |= condition;

	if (PlayerStat & STAT_PUSH) //경직
	{
		//상태이상 알림.
		player->UiText->ConditionChecker(4);

		player->m_bPlayTakeDamageAnimation = true;
		player->PlayKnockbackAnimation();
		FVector HitNormal = value;
		player->GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		player->LaunchCharacter((-HitNormal.GetSafeNormal()) * 5000, true, true);

		FTimerDelegate KnockbackEndDelegate = FTimerDelegate::CreateUObject(this, &UCondition::KnockbackEnd, player);
		GetWorld()->GetTimerManager().SetTimer(KnockbackEndTimerHandle, KnockbackEndDelegate, 0.1f, false);
	}
}

template<>
inline void UCondition::AddCondition<float>(int condition, AMyPlayer * player, float value) {
	//상태 추가
	PlayerStat |= condition;

	if (PlayerStat & STAT_MANABURN) //마나번
	{
		//상태이상 알림.
		player->UiText->ConditionChecker(3);
		float percent = (float)value;

		//일정 값만큼 마나가 깎임.
		ExecuteManaPercentBurn(player, percent);
	}
}