// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicSkill.h"
#include "MySkill03.generated.h"

/**
 * ������ ��ų �۾�.
 */
UCLASS()
class CURSEOFDESIRE_API AMySkill03 : public ABasicSkill
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AMySkill03();
protected:
	virtual void BeginPlay() override;

public:
	//���� ��ƼŬ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * BuffEffect;

	class AMyPlayer* player;

	virtual void Execute();

	UPROPERTY()
	FTimerHandle m_SkillEndTimer;

	UFUNCTION()
	void EndSkill();

	//��ų ���ӽð�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	float SkillDuration = 10.0f;
};
