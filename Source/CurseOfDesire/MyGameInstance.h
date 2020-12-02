// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FDele_Multi);
DECLARE_DELEGATE(FDele_Single);
DECLARE_DELEGATE_OneParam(FDele_Single_OneIntParam, int32);
UCLASS()
class CURSEOFDESIRE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	//TSubclassOf<class UEffectPlayer> EffectClass;

#pragma region 슬로우모션
private:
	UPROPERTY()
	bool isSlowMotion = false;

public:
	//슬로우 모션 시작
	UFUNCTION()
	void StartSlowMotion();

	//슬로우 모션 종료
	UFUNCTION()
	void EndSlowMotion();

#pragma endregion 슬로우모션

#pragma region 콤보시스템
private:
	UPROPERTY()
	int combo = 0; // 콤보

	UPROPERTY()
	int maximumCombo = 0; //최대콤보

	UPROPERTY()
	FTimerHandle comboResetTimer; //콤보 초기화 타이머

public:
	//콤보 유지 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float comboHoldingTime = 1.0f;

public:
	//콤보, 최대콤보 초기화
	UFUNCTION()
	void InitCombos();

	//콤보 추가.
	UFUNCTION()
	void AddCombo();

	//콤보 수 얻기
	UFUNCTION(BlueprintPure, Category = Combo)
	int GetCombo();

	//최대 콤보 수 얻기
	UFUNCTION(BlueprintPure, Category = Combo)
	int GetMaximumCombo();

	//콤보 초기화
	UFUNCTION()
	void ResetCombo();

#pragma endregion 콤보시스템

#pragma region 업적_2
private:
	//몬스터 죽인 횟수
	UPROPERTY()
	int killMonsterCount = 0;

public:
	//몬스터 죽인 횟수 초기화
	UFUNCTION()
	void KillMonsterCountInit();

	//몬스터 죽인 횟수 추가
	UFUNCTION()
	void AddKillMonsterCount();

	//몬스터 죽인 횟수 얻기
	UFUNCTION(BlueprintPure, Category = Achievements)
	int GetKillMonsterCount();

#pragma endregion 업적_2

#pragma region 카메라 흔들기
public:
	//카메라 흔들기 실행.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShake> MyShake;

	//카메라 흔들기 실행.
	UFUNCTION()
	void PlayCameraShake();

#pragma endregion 카메라 흔들기

#pragma region 플레이어 막기
public:
	//몬스터 죽었을 때 대리자
	FDele_Multi Fuc_DeleMonsterDie;

#pragma endregion 플레이어 막기

#pragma region 스킬 언락하기
public:
	//스킬 언락 대리자
	FDele_Single Fuc_UltimateSkillUnlock;
	UFUNCTION()
	void UltimateSkillUnlock();
#pragma endregion 스킬 언락하기

#pragma region 플레이어 공격에 몬스터가 맞았다.
public:
	//몬스터 hit 대리자
	FDele_Single_OneIntParam Fuc_HitMonster;

	UFUNCTION()
	void MonsterHitNotice(int type);

#pragma endregion 플레이어 공격에 몬스터가 맞았다.
};