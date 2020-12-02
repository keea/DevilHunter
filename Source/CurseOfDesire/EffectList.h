// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectList.generated.h"

UENUM(BlueprintType)
enum class EEFFECTS : uint8 {
	NONE UMETA(DisplayName = "사용하지 않는 값입니다. 맵 생성시 중복되지 않도록 처리하기 위해."),
	player_skill3_3_2 UMETA(DisplayName = "player_skill3_3_2_스킬3 시전 시 플레이어의 손에 잠시 나타났다가 사라진다."),
	player_ult UMETA(DisplayName = "player_ult_플레이어 각성기"),
	player_revive2 UMETA(DisplayName = "player_revive2_플레이어 부활 시"),
	player_sttifen UMETA(DisplayName = "player_sttifen_플레이어 상태 이상-경직 상태 시"),
	player_groundspark UMETA(DisplayName = "player_groundspark_플레이어 스킬 사용 후 땅이 갈라진다.(땅 내려직는 스킬 한정)"),
	player_manaburn_char UMETA(DisplayName = "player_manaburn_char_플레이어 상태 이상-마나번 상태(플레이어 몸에 적용)"),
	player_manaburn_Mpbar UMETA(DisplayName = "player_manaburn_Mpbar_플레이어 상태 이상-마나번 상태(MP바에 적용)"),
	player_critical1 UMETA(DisplayName = "player_critical1_플레이어 크리티컬 발생 시"),
	player_skill3_ribbon UMETA(DisplayName = "player_skill3_ribbon_플레이어 스킬3 활성화 상태에서 기본 공격 시 따라다니는 궤적"),
	player_attack_1_2 UMETA(DisplayName = "player_attack_1_2_플레이어 기본 공격 1타-2타 시 생기는 궤적"),
	player_attack_3 UMETA(DisplayName = "player_attack_3_플레이어 기본 공격 3타 시 생기는 궤적"),
	player_skill1 UMETA(DisplayName = "player_skill1_플레이어 스킬1 시전 시 생기는 스크래치 형태"),
	player_stun UMETA(DisplayName = "player_stun_플레이어 상태이상-스턴 상태 시"),
	Player_skill2 UMETA(DisplayName = "Player_skill2_플레이어 스킬2 시전 시 날아가는 검기"),
	player_skill4 UMETA(DisplayName = "player_skill4_플레이어 스킬4 시전 시 땅을 타고 나아가는 스파크"),
	player_potionHP UMETA(DisplayName = "player_potionHP_플레이어 HP포션 사용 시 10초간 몸에 맴도는 붉은 잔상"),
	player_potionMP UMETA(DisplayName = "player_potionMP_플레이어 MP포션 사용 시 맴도는 푸른 잔상"),
	player_dash UMETA(DisplayName = "player_dash_플레이어 대쉬 사용 시"),
	player_evade UMETA(DisplayName = "player_evade_플레이어 회피 동작 시 "),
	player_poison UMETA(DisplayName = "player_poison_플레이어 상태 이상-중독 상태 시"),
	player_ult_char UMETA(DisplayName = "player_ult_char_각성기 사용 후 플레이어 몸에 잠시 남아있는 효과"),
	player_skill4_spark_body UMETA(DisplayName = "player_skill4_spark_body_스킬4 사용 후 플레이어의 몸에 잠시 남아 있는 효과"),
	blood1 UMETA(DisplayName = "blood1_피격 시 각각 25%의 확률로 발생"),
	blood2 UMETA(DisplayName = "blood2_피격 시 각각 25%의 확률로 발생"),
	blood3 UMETA(DisplayName = "blood3_피격 시 각각 25%의 확률로 발생"),
	blood4 UMETA(DisplayName = "blood4_피격 시 각각 25%의 확률로 발생"),
	portal_circle_1Stage UMETA(DisplayName = "portal_circle_1Stage_1스테이지->중간 보스 방으로 이어지는 포탈"),
	Stage1_barrier UMETA(DisplayName = "1Stage_barrier_다음 구간으로 넘어가지 못하게 막아놓은 결계"),
	portal_2Stage UMETA(DisplayName = "portal_2Stage_2스테이지->최종 보스 방으로 이어지는 포탈"),
	UI_loading UMETA(DisplayName = "UI_loading_로딩창에서 로딩바의 게이지가 다 찼을 때 로딩바에 적용"),
	M_dissolve1 UMETA(DisplayName = "M_dissolve1_일반 몬스터&순찰병 사망 시(원하는대로 색 변화 가능)"),
	player_attack_spark1 UMETA(DisplayName = "player_attack_spark1_플레이어의 스킬이 몬스터에게 닿았을 때, 몬스터에게 잠시 잔류"),
	player_attack_spark2 UMETA(DisplayName = "player_attack_spark2_플레이어의 스킬이 몬스터에게 닿았을 때, 몬스터에게 잠시 잔류"),
	player_monsterskill2 UMETA(DisplayName = "player_monsterskill2_플레이어의 스킬이 몬스터에게 닿았을 때, 몬스터에게 잠시 잔류"),
	m_attack UMETA(DisplayName = "m_attack_일반 몬스터, 순찰병 기본 공격 시 "),
	m_recog UMETA(DisplayName = "m_recog_순찰병 플레이어 인식 시(머리 부근에 느낌표 발생)"),
	mb_skill1_summ UMETA(DisplayName = "mb_skill1_summ_중간 보스 스킬1 시전 시(꽃 생성 시 dissolve효과 적용)"),
	mb_skill1_disa UMETA(DisplayName = "mb_skill1_disa_중간 보스 스킬1(꽃 소멸 시 M_dissolve2)"),
	mb_heal_circle UMETA(DisplayName = "mb_heal_circle_중간 보스 스킬1 꽃에 의한 체력 회복 시, 중간 보스의 몸 밑에 생기는 이펙트"),
	mb_explosion2 UMETA(DisplayName = "mb_explosion2_중간 보스 스킬2"),
	mb_skill3_summ UMETA(DisplayName = "mb_skill3_summ_중간 보스 스킬3(몬스터 소환 시)"),
	mb_skill3_explosion UMETA(DisplayName = "mb_skill3_explosion_중간 보스 스킬3(몬스터 소멸 시)"),
	mb_skill3_explosion2 UMETA(DisplayName = "mb_skill3_explosion2_중간 보스 스킬3(몬스터 소멸 시)"),
	mb_death UMETA(DisplayName = "mb_death_중간 보스 사망 시(시체는 그대로 남고 반짝이 효과만)"),
	mb_attack2_1 UMETA(DisplayName = "mb_attack2_1_중간 보스 기본 공격 시"),
	fb_skill4_earthquake UMETA(DisplayName = "fb_skill4_earthquake_최종 보스 지진"),
	fb_skill5_manaburn UMETA(DisplayName = "fb_skill5_manaburn_최종 보스 마나번 "),
	fb_skill4_bottom UMETA(DisplayName = "fb_skill4_bottom_최종 보스 스킬4 종료 후 바닥에 남는 잔류물(삭제 고려)"),
	fb_skill3_teleport UMETA(DisplayName = "fb_skill3_teleport_최종 보스 순간 이동 시"),
	fb_skill1_directDeath UMETA(DisplayName = "fb_skill1_directDeath_최종 보스 스킬1 즉사 패턴 사용 시(창 메시 필요)"),
	fb_skill1_charge_aura UMETA(DisplayName = "fb_skill1_charge_aura_최종 보스 스킬1 캐스팅 시(directDeath와 합쳐야 함)"),
	fb_skill2_swish UMETA(DisplayName = "fb_skill2_swish_최종 보스 스킬2 사용 시"),
	fb_death UMETA(DisplayName = "fb_death_최종 보스 사망 시"),
	fb_fury UMETA(DisplayName = "fb_fury_최종 보스 광폭화 시(약간의 스모그)"),
	fb_skill6_sword UMETA(DisplayName = "fb_skill6_sword_최종 보스 스킬6 포탈이 열린 뒤 날아가는 검 이펙트들(삭제고려)"),
	END UMETA(DisplayName = "사용하지 않는 값입니다."),
};

class UParticleSystem;    //전방 선언

/**
 *
 */
UCLASS(Blueprintable)
class CURSEOFDESIRE_API UEffectList : public UObject
{
	GENERATED_BODY()
public:
	UEffectList();

	//이펙트 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = sound, meta = (AllowPrivateAccess = "true"))
		TMap<TEnumAsByte<EEFFECTS>, UParticleSystem * > EffectList;

	UFUNCTION()
		UParticleSystem * GetEffect(TEnumAsByte<EEFFECTS> effectIdx);
};
