// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundCue.h"
#include "SoundList.generated.h"

UENUM(BlueprintType)
enum class ESOUNDS : uint8
{
	NONE UMETA(DisplayName = "사용하지 않는 값입니다. 맵 생성시 중복되지 않도록 처리하기 위해."),
	SOUND0 UMETA(DisplayName = "[배경음악] 게임 시작&메인 화면 BGM"),
	SOUND1 UMETA(DisplayName = "[배경음악] 1 STAGE BGM & 1.5 STAGE BGM"),
	SOUND2 UMETA(DisplayName = "[배경음악] 2 STAGE BGM"),
	SOUND3 UMETA(DisplayName = "[배경음악] 1 STAGE BGM2"),
	SOUND4 UMETA(DisplayName = "[배경음악] 광폭화"),
	SOUND5 UMETA(DisplayName = "[배경음악] Credit BGM"),
	SOUND6 UMETA(DisplayName = "[배경음악] 홍보 영상 BGM"),
	SOUND7 UMETA(DisplayName = "[기타 효과음] 게임 시작 버튼(UI)"),
	SOUND8 UMETA(DisplayName = "[기타 효과음] 게임 종료 버튼(UI)"),
	SOUND9 UMETA(DisplayName = "[기타 효과음] 캐릭터 창- 다음 버튼(UI)"),
	SOUND10 UMETA(DisplayName = "[기타 효과음] 설정 창 버튼(UI)"),
	SOUND11 UMETA(DisplayName = "[기타 효과음] 시작 지점- 성문"),
	SOUND12 UMETA(DisplayName = "[기타 효과음] 스테이지 클리어"),
	SOUND13 UMETA(DisplayName = "[기타 효과음] 스테이지 클리어 실패"),
	SOUND14 UMETA(DisplayName = "[기타 효과음] 최종 스테이지 클리어"),
	SOUND15 UMETA(DisplayName = "[기타 효과음] 보스 등장"),
	SOUND16 UMETA(DisplayName = "[기타 효과음] 점수"),
	SOUND17 UMETA(DisplayName = "[기타 효과음] 업적 클리어 "),
	SOUND18 UMETA(DisplayName = "[기타 효과음] 업적 보상"),
	SOUND19 UMETA(DisplayName = "[기타 효과음] 스킬 활성화(UI)"),
	SOUND20 UMETA(DisplayName = "[기타 효과음] 각성 활성화(UI)"),
	SOUND21 UMETA(DisplayName = "[기타 효과음] 이동 도중 효과음"),
	SOUND22 UMETA(DisplayName = "[기타 효과음] 물 효과음"),
	SOUND23 UMETA(DisplayName = "[기타 효과음] 횃불 효과음"),
	SOUND24 UMETA(DisplayName = "[기타 효과음] 게임 오버 시 효과음"),
	SOUND25 UMETA(DisplayName = "[기타 효과음] 게임 종료 후 점수 창 효과음"),
	SOUND26 UMETA(DisplayName = "[기타 효과음] 여성의 웃음 소리"),
	SOUND27 UMETA(DisplayName = "[기타 효과음] 휘파람-새 소리"),
	SOUND28 UMETA(DisplayName = "[캐릭터 음성] 기본 공격"),
	SOUND29 UMETA(DisplayName = "[캐릭터 음성] 대쉬"),
	SOUND30 UMETA(DisplayName = "[캐릭터 음성] 회피"),
	SOUND31 UMETA(DisplayName = "[캐릭터 음성] 2단 회피"),
	SOUND32 UMETA(DisplayName = "[캐릭터 음성] 피격1"),
	SOUND33 UMETA(DisplayName = "[캐릭터 음성] 피격2"),
	SOUND34 UMETA(DisplayName = "[캐릭터 음성] 피격3"),
	SOUND35 UMETA(DisplayName = "[캐릭터 음성] 피격4"),
	SOUND36 UMETA(DisplayName = "[캐릭터 음성] 피격5"),
	SOUND37 UMETA(DisplayName = "[캐릭터 음성] 크리티컬"),
	SOUND38 UMETA(DisplayName = "[캐릭터 음성] 스킬1"),
	SOUND39 UMETA(DisplayName = "[캐릭터 음성] 스킬2"),
	SOUND40 UMETA(DisplayName = "[캐릭터 음성] 스킬3"),
	SOUND41 UMETA(DisplayName = "[캐릭터 음성] 스킬4"),
	SOUND42 UMETA(DisplayName = "[캐릭터 음성] 각성"),
	SOUND43 UMETA(DisplayName = "[캐릭터 음성] 적 처치1"),
	SOUND44 UMETA(DisplayName = "[캐릭터 음성] 적 처치2"),
	SOUND45 UMETA(DisplayName = "[캐릭터 음성] 피격"),
	SOUND46 UMETA(DisplayName = "[캐릭터 음성] 위험"),
	SOUND47 UMETA(DisplayName = "[캐릭터 음성] 사망"),
	SOUND48 UMETA(DisplayName = "[캐릭터 음성] 부활"),
	SOUND49 UMETA(DisplayName = "[캐릭터 효과음] 기본 공격"),
	SOUND50 UMETA(DisplayName = "[캐릭터 효과음] 대쉬"),
	SOUND51 UMETA(DisplayName = "[캐릭터 효과음] 회피"),
	SOUND52 UMETA(DisplayName = "[캐릭터 효과음] 2단 회피"),
	SOUND53 UMETA(DisplayName = "[캐릭터 효과음] 크리티컬"),
	SOUND54 UMETA(DisplayName = "[캐릭터 효과음] 이동"),
	SOUND55 UMETA(DisplayName = "[캐릭터 효과음] 기본 공격"),
	SOUND56 UMETA(DisplayName = "[캐릭터 효과음] 피격1"),
	SOUND57 UMETA(DisplayName = "[캐릭터 효과음] 피격2"),
	SOUND58 UMETA(DisplayName = "[캐릭터 효과음] 피격3"),
	SOUND59 UMETA(DisplayName = "[캐릭터 효과음] 피격4"),
	SOUND60 UMETA(DisplayName = "[캐릭터 효과음] 피격5"),
	SOUND61 UMETA(DisplayName = "[캐릭터 효과음] 스킬1"),
	SOUND62 UMETA(DisplayName = "[캐릭터 효과음] 스킬2"),
	SOUND63 UMETA(DisplayName = "[캐릭터 효과음] 스킬3"),
	SOUND64 UMETA(DisplayName = "[캐릭터 효과음] 스킬4"),
	SOUND65 UMETA(DisplayName = "[캐릭터 효과음] 각성"),
	SOUND66 UMETA(DisplayName = "[캐릭터 효과음] 포션"),
	SOUND67 UMETA(DisplayName = "[캐릭터 효과음] 위험"),
	SOUND68 UMETA(DisplayName = "[캐릭터 효과음] 사망"),
	SOUND69 UMETA(DisplayName = "[캐릭터 효과음] 부활"),
	SOUND70 UMETA(DisplayName = "[일반 몬스터 음성] 등장"),
	SOUND71 UMETA(DisplayName = "[일반 몬스터 음성] 공격"),
	SOUND72 UMETA(DisplayName = "[일반 몬스터 음성] 피격1"),
	SOUND73 UMETA(DisplayName = "[일반 몬스터 음성] 피격2"),
	SOUND74 UMETA(DisplayName = "[일반 몬스터 음성] 피격3"),
	SOUND75 UMETA(DisplayName = "[일반 몬스터 음성] 피격4"),
	SOUND76 UMETA(DisplayName = "[일반 몬스터 음성] 사망"),
	SOUND77 UMETA(DisplayName = "[일반 몬스터 효과음] 이동"),
	SOUND78 UMETA(DisplayName = "[일반 몬스터 효과음] 공격"),
	SOUND79 UMETA(DisplayName = "[일반 몬스터 효과음] 피격1"),
	SOUND80 UMETA(DisplayName = "[일반 몬스터 효과음] 피격2"),
	SOUND81 UMETA(DisplayName = "[일반 몬스터 효과음] 피격3"),
	SOUND82 UMETA(DisplayName = "[일반 몬스터 효과음] 피격4"),
	SOUND83 UMETA(DisplayName = "[일반 몬스터 효과음] 사망"),
	SOUND84 UMETA(DisplayName = "[순찰병 음성] 인식"),
	SOUND85 UMETA(DisplayName = "[순찰병 효과음] 인식"),
	SOUND86 UMETA(DisplayName = "[중간 보스 음성] 공격"),
	SOUND87 UMETA(DisplayName = "[중간 보스 음성] 공격 패턴 1"),
	SOUND88 UMETA(DisplayName = "[중간 보스 음성] 공격 패턴 2"),
	SOUND89 UMETA(DisplayName = "[중간 보스 음성] 공격 패턴 3"),
	SOUND90 UMETA(DisplayName = "[중간 보스 음성] 피격1"),
	SOUND91 UMETA(DisplayName = "[중간 보스 음성] 피격2"),
	SOUND92 UMETA(DisplayName = "[중간 보스 음성] 피격3"),
	SOUND93 UMETA(DisplayName = "[중간 보스 음성] 피격4"),
	SOUND94 UMETA(DisplayName = "[중간 보스 음성] 각성 피격"),
	SOUND95 UMETA(DisplayName = "[중간 보스 음성] 빈사 상태"),
	SOUND96 UMETA(DisplayName = "[중간 보스 음성] 사망"),
	SOUND97 UMETA(DisplayName = "[중간 보스 음성] 간헐적으로 나오는 음성"),
	SOUND98 UMETA(DisplayName = "[중간 보스 효과음] 공격"),
	SOUND99 UMETA(DisplayName = "[중간 보스 효과음] 공격 패턴 1"),
	SOUND100 UMETA(DisplayName = "[중간 보스 효과음] 공격 패턴 2"),
	SOUND101 UMETA(DisplayName = "[중간 보스 효과음] 공격 패턴 3"),
	SOUND102 UMETA(DisplayName = "[중간 보스 효과음] 피격1"),
	SOUND103 UMETA(DisplayName = "[중간 보스 효과음] 피격2"),
	SOUND104 UMETA(DisplayName = "[중간 보스 효과음] 피격3"),
	SOUND105 UMETA(DisplayName = "[중간 보스 효과음] 피격4"),
	SOUND106 UMETA(DisplayName = "[중간 보스 효과음] 각성 피격"),
	SOUND107 UMETA(DisplayName = "[중간 보스 효과음] 빈사 상태"),
	SOUND108 UMETA(DisplayName = "[중간 보스 효과음] 사망"),
	SOUND109 UMETA(DisplayName = "[최종 보스 음성] 공격"),
	SOUND110 UMETA(DisplayName = "[최종 보스 음성] 공격 패턴 1"),
	SOUND111 UMETA(DisplayName = "[최종 보스 음성] 공격 패턴 2"),
	SOUND112 UMETA(DisplayName = "[최종 보스 음성] 공격 패턴 3"),
	SOUND113 UMETA(DisplayName = "[최종 보스 음성] 공격 패턴 4"),
	SOUND114 UMETA(DisplayName = "[최종 보스 음성] 공격 패턴 5"),
	SOUND115 UMETA(DisplayName = "[최종 보스 음성] 피격"),
	SOUND116 UMETA(DisplayName = "[최종 보스 음성] 각성 피격"),
	SOUND117 UMETA(DisplayName = "[최종 보스 음성] 빈사 상태"),
	SOUND118 UMETA(DisplayName = "[최종 보스 음성] 광폭화"),
	SOUND119 UMETA(DisplayName = "[최종 보스 음성] 사망"),
	SOUND120 UMETA(DisplayName = "[최종 보스 음성] 간헐적으로 웃는 음성"),
	SOUND121 UMETA(DisplayName = "[최종 보스 효과음] 공격"),
	SOUND122 UMETA(DisplayName = "[최종 보스 효과음] 공격 패턴 1"),
	SOUND123 UMETA(DisplayName = "[최종 보스 효과음] 공격 패턴 2"),
	SOUND124 UMETA(DisplayName = "[최종 보스 효과음] 공격 패턴 3"),
	SOUND125 UMETA(DisplayName = "[최종 보스 효과음] 공격 패턴 4"),
	SOUND126 UMETA(DisplayName = "[최종 보스 효과음] 공격 패턴 5"),
	SOUND127 UMETA(DisplayName = "[최종 보스 효과음] 공격 패턴 6"),
	SOUND128 UMETA(DisplayName = "[최종 보스 효과음] 피격"),
	SOUND129 UMETA(DisplayName = "[최종 보스 효과음] 각성 피격"),
	SOUND130 UMETA(DisplayName = "[최종 보스 효과음] 빈사 상태"),
	SOUND131 UMETA(DisplayName = "[최종 보스 효과음] 광폭화"),
	SOUND132 UMETA(DisplayName = "[최종 보스 효과음] 사망"),
	END UMETA(DisplayName = "사용하지 않는 값입니다."),
};

/**
 *
 */
 //사운드 바뀌는 것 하는 델리게이터
DECLARE_MULTICAST_DELEGATE_OneParam(FDele_Multi_OneParam, TEnumAsByte<ESOUNDS>);

UCLASS(Blueprintable)
class CURSEOFDESIRE_API USoundList : public UObject
{
	GENERATED_BODY()

public:
	USoundList();

	//사운드 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = sound, meta = (AllowPrivateAccess = "true"))
	TMap<TEnumAsByte<ESOUNDS>, USoundCue * > SoundList;

	UFUNCTION()
	USoundCue * GetSound(TEnumAsByte<ESOUNDS> soundIdx);
	
	FDele_Multi_OneParam Fuc_DeleMulti_SoundChange;

#if WITH_EDITOR
	//프로퍼티 변경될 때 마다 사운드 값 변경
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	UPROPERTY()
	TMap<TEnumAsByte<ESOUNDS>, USoundCue * > BeforeSoundList;
};
