// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillInfo.h"
#include "Itf_AnimationNotify.h"
#include "SkillManager.generated.h"

UCLASS()
class CURSEOFDESIRE_API ASkillManager : public AActor, public IItf_AnimationNotify
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//스킬 초기화
	UFUNCTION()
	void ResetSkill(int type);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	TArray<FSkillInfo> SkillInfo;

	//스킬 사용
	UFUNCTION()
	bool UseSkill(class AMyPlayer * player, int type);

	//스킬 사용하기
	UFUNCTION()
	void Skill01();

	//스킬 사용하기
	UFUNCTION()
	void Skill02();
	
	//스킬 사용하기
	UFUNCTION()
	void Skill03();

	//스킬 사용하기
	UFUNCTION()
	void Skill04();

	//궁극기 스킬 사용하기
	UFUNCTION()
	void SkillUltimate();

	//스킬 애니메이션 노티파이 받기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill_Anim")
	void Itf_Skill_Anim(int skillType);
	virtual void Itf_Skill_Anim_Implementation(int skillType) override;

	//스킬 종료 노티파이 받기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Skill_End(int skillType);
	virtual void Itf_Skill_End_Implementation(int skillType) override;

	//궁극기 스킬 언락
	UFUNCTION()
		void UltimateSkillUnlock();

private:
	UPROPERTY()
	bool isFail;

	UPROPERTY()
	class AMyPlayer * p_Player;

	UFUNCTION()
	void FailSkill(int skillType);
};
