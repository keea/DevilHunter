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

	//��ų �ʱ�ȭ
	UFUNCTION()
	void ResetSkill(int type);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	TArray<FSkillInfo> SkillInfo;

	//��ų ���
	UFUNCTION()
	bool UseSkill(class AMyPlayer * player, int type);

	//��ų ����ϱ�
	UFUNCTION()
	void Skill01();

	//��ų ����ϱ�
	UFUNCTION()
	void Skill02();
	
	//��ų ����ϱ�
	UFUNCTION()
	void Skill03();

	//��ų ����ϱ�
	UFUNCTION()
	void Skill04();

	//�ñر� ��ų ����ϱ�
	UFUNCTION()
	void SkillUltimate();

	//��ų �ִϸ��̼� ��Ƽ���� �ޱ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill_Anim")
	void Itf_Skill_Anim(int skillType);
	virtual void Itf_Skill_Anim_Implementation(int skillType) override;

	//��ų ���� ��Ƽ���� �ޱ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
	void Itf_Skill_End(int skillType);
	virtual void Itf_Skill_End_Implementation(int skillType) override;

	//�ñر� ��ų ���
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
