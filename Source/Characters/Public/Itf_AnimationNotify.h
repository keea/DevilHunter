// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Itf_AnimationNotify.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItf_AnimationNotify : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARACTERS_API IItf_AnimationNotify
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//콤보가 취소될 때 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
	void Itf_ResetCombo();

	//피격 애니메이션이 끝날 때 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
	void Itf_EndTakeDamage();

	//죽음 애니메이션이 끝날 때 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
	void Itf_DeathAnimEnd();

	//부활 애니메이션이 끝날 때 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
	void Itf_ResurrectionAnimEnd();

	//사망할 때 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_PlayerState")
	void Itf_PlayerDie();

	//부활할 때 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_PlayerState")
	void Itf_PlayerResurrection();

	//몬스터 공격 끝
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MonATK();

	//스킬 타이밍 조절
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill_Anim")
	void Itf_Skill_Anim(int skillType);

	//스킬 종료 타이밍
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Skill_End(int skillType);

	//스킬데미지 전달
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Skill_Damage(float damage);

	//궁극기 스킬 사용시 카메라 전환
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Skill_Ultimate_Start();

	//궁극기 스킬 종료 시 카메라 전환
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Skill_Ultimate_End();

	//버프형 스킬 시작 알림.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Skill_Buff_Start();

	//버프형 스킬 지속시간 종료 알림.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Skill_Buff_End();

	//회피 애니메이션 종료 알림.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Avoid_End();

	//몬스터 공격 시작
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MonATK_START();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MonHIT_End();

	//중간 보스 몬스터 소환
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill1_End();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill2_Start();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill2_End();	

	//스킬 애니메이션 종료하는가?
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
		void Itf_Skill_Anim_End(int skillType);

	//중간 보스 꽃 소환
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill3_End();

	//중간 보스 꽃 소환
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill3_Start();

	//최종보스
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill1_Start();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill2_Start();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill3_Start();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill4_Start();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill4_End();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill5_Start();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill5_End();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill6_Start();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill6_End();
	//스턴 애니메이션 끝
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
	void Itf_StunAnimEnd();
};
