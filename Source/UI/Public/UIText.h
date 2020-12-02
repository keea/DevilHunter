// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "UIText.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIDelegate);

UCLASS()
class UI_API UUIText : public UObject
{
	GENERATED_BODY()
private:
	class AMyPlayer * player;

	UPROPERTY()
		FTimerHandle HpPotion_timer;

	UPROPERTY()
		FTimerHandle MpPotion_timer;

	UPROPERTY()
		int deadcount = 4;

public:
	UUIText();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool FBTimeOut = false;

	UFUNCTION()
	void SetInit(AMyPlayer * player);

	//MP숫자 표시
	UFUNCTION(BlueprintPure, Category = Stats)
	FText GetMPIntText();

	//HP숫자 표시
	UFUNCTION(BlueprintPure, Category = Stats)
	FText GetHPIntText();

	UFUNCTION()
		void ExecuteHpPortionTimer(float coolTime);

	UFUNCTION()
		void ExecuteMpPortionTimer(float coolTime);

	UFUNCTION()
		void SkillChecker(int type, FTimerHandle timerHander, float Cooldown);

	UFUNCTION()
		void NotSkillCheck();

	UFUNCTION()
		void NotPotionCheck();

	UFUNCTION()
		void ConditionChecker(int Conditonnum);

	UFUNCTION()
		void HPCheck();

	UFUNCTION()
		void MPCheck();

	UFUNCTION()
		void DashCheck();

	UFUNCTION()
		void DeadCheck();

	UFUNCTION()
		void MBFlowerCheck();

	UFUNCTION(BlueprintPure)
		int GetDeadCount();

	UFUNCTION(BlueprintCallable)
		void MinusDeadCount();

	UFUNCTION()
		void FBBerserk();

	UFUNCTION()
		void UnlockAwake();

	UFUNCTION()
		void CreateCombo();

	UFUNCTION()
		void MonHp();

	UFUNCTION(BlueprintCallable)
		void FBTimeOutCheck();

	UFUNCTION()
		void Pvasion();

public:
	//MP 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate MpProgress;

	//HP가 소모시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate HpProgress;

	//Dash 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate DashProgress;

	//HP 포션 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate HPPotionProgress;

	//MP 포션 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate MPPotionProgress;

	//콤보 횟수가 추가 되면 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate ComboProgress;

	//스킬 1 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate Skill1Progress;

	//스킬 2 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate Skill2Progress;

	//스킬 3 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate Skill3Progress;

	//스킬 4 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate Skill4Progress;

	//중독 실행 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate PoisonProgress;

	//기절 실행 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate FaintProgress;

	//마나 번 실행 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate ManaburnProgress;

	//경직 실행 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate StiffnessProgress;

	//스킬 실행 실패 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate NotSkillProgress;

	//포션 실행 실패 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate NotPotionProgress;

	//사망 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate DeadProgress;

	//MB가 꽃을 소환 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate FlowerProgress;

	//각성 스킬 사용 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate AwaikingProgress;

	//광폭화 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate BerserkProgress;

	//각성 스킬 해제 시 호출
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate UnlockAwaikProgress;

	//몬스터 hp 이벤트
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate MonsterHpProgress;

	//회피 이벤트
	UPROPERTY(BlueprintAssignable, Category = "Ui")
		FUIDelegate evasionProgress;
};
