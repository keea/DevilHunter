#pragma once

#include "CoreMinimal.h"
#include "CurseOfDesire.h"
#include "SkillInfo.generated.h"

USTRUCT(BlueprintType)
struct CURSEOFDESIRE_API FSkillInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FSkillInfo();

	//스킬 ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	int SkillID;

	//데미지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	float Damage;

	//소모 MP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	int MP;

	//쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	float Cooldown;

	//스킬명
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	FString Name;

	//스킬 애니메이션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* UseSkillMontages;

	//스킬 애니메이션(검)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* UseSkillBladeMontages;

	//스킬을 사용할 수 있는가
	UPROPERTY()
	bool isCanSkill;

	//스킬 관련 쿨타임 타이머
	UPROPERTY()
	FTimerHandle m_UnUsedSkillTimer;

	//스킬 애니메이션 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float AnimSpeed = 1.0f;

	//스킬이 언락 상태인가?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	bool isUnRock;

	//스킬 생성 블루프린터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	TSubclassOf<class ABasicSkill> SkillClass;
};