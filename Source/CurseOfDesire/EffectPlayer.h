// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectPlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CURSEOFDESIRE_API UEffectPlayer : public UObject
{
	GENERATED_BODY()

public:
	//플레이어 부활 시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerReviveEffect;

	//플레이어 상태 이상-경직 상태 시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerSttifenEffect;

	//플레이어 상태 이상-마나번 상태(플레이어 몸에 적용)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerManaburnChar;

	//플레이어 크리티컬 발생 시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerCritical;

	//플레이어 스킬3 활성화 상태에서 기본 공격 시 따라다니는 궤적
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerSkill3Ribbon;

	//1스테이지->중간 보스 방으로 이어지는 포탈
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stage1, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PortalCircle_1Stage;

	//2스테이지->최종 보스 방으로 이어지는 포탈
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stage2, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PortalCircle_2Stage;

	//플레이어의 스킬이 몬스터에게 닿았을 때, 몬스터에게 잠시 잔류
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerAttackSpark1;

	//플레이어의 스킬이 몬스터에게 닿았을 때, 몬스터에게 잠시 잔류
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerAttackSpark2;

	//플레이어의 스킬이 몬스터에게 닿았을 때, 몬스터에게 잠시 잔류
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerAttackSpark3;

	//일반 몬스터 기본 공격 시 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * M_Attack;

	//순찰병 플레이어 인식 시(머리 부근에 느낌표 발생)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * M_Recog;

	//중간 보스 스킬1(꽃 소환 시)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiddleBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * MbSkill1Summ;

	//중간 보스 스킬2
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiddleBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * MbExplosion2;

	//중간 보스 스킬3(몬스터 소환 시)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiddleBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * MbSkill3;

	//중간 보스 스킬3(몬스터 소멸 시)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiddleBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * MbSkill3Explosion;

	//중간 보스 스킬3(몬스터 소멸 시)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiddleBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * MbSkill3Explosion2;

	//중간 보스 사망 시(돌 조각으로 변해 흩날려 사라진다)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiddleBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * MbDeath;

	//중간 보스 기본 공격 시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MiddleBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * MbAttack;

	//최종 보스 지진
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbSkill4Earthquake;

	//최종 보스 마나번
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbSkill5Manaburn;

	//최종 보스 스킬4 종료 후 바닥에 남는 잔류물(삭제 고려)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem * FbSkill4Bottom;

	//최종 보스 스킬4 종료 후 바닥에 일어나는 불길(earthquake와 합쳐야 함)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbSkill4FireRoad;

	//최종 보스 순간 이동 시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbSkill3Teleport;

	//최종 보스 스킬1 즉사 패턴 사용 시(창 메시 필요)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbSkill1DirectDeath;

	//최종 보스 스킬1 캐스팅 시(directDeath와 합쳐야 함)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbSkill1ChargeAura;

	//최종 보스 스킬2 사용 시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbSkill2Swish;

	//최종 보스 사망 시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbDeath;

	//최종 보스 광폭화 시(약간의 스모그)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FinalBoss, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * FbFury;
};
