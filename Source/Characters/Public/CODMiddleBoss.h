// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonsterClass.h"
#include "MBFlower.h"
#include "CODMiddleBoss.generated.h"

/**
 *
 */
UCLASS()
class CHARACTERS_API ACODMiddleBoss : public ABaseMonsterClass
{
	GENERATED_BODY()
		virtual void Tick(float DeltaTime) override;
	ACODMiddleBoss();

	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	bool skill3check;
	bool decide;
	int currentState;
	int PrevIndex;
	//���� 3 : �� ��ȯ ���� 2 : ������ ���� 1 : �� ��ȯ
	//������Ʈ ��� : ����3 ����2 ����1 ������ Ȯ�������� ����2:80 ����1:20 ����2 ����1(2) ����2 ����2 ����1 ����2����2 hp 10%���� ���(1����) ���� ���� HP ���� �� ���
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage * >	MBAnimMontages;*/

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AActor> SpawnToMonster;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AMBFlower> SpawnToFlower;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AActor> SpawnToSkill2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MBPattern")
		AMBFlower* flower1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MBPattern")
		AMBFlower* flower2;

	UFUNCTION()
		void Reset();

	UFUNCTION()
		void SpawnObject();

	UFUNCTION()
		void SpawnFlower();

	UFUNCTION()
		void SpawnMBSkill2();

	UFUNCTION()
		void PlayPattern();

	UFUNCTION()
		void Pattern();

	UFUNCTION()
		void CheckFaint();



	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBSkill01")
		bool m_isRecover;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBSkill01")
		bool m_isSkillDestroy;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MBPattern")
		bool skill1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MBPattern")
		bool skill2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MBPattern")
		bool skill3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MBPattern")
		bool die;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBPattern")
		bool faint;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBPattern")
		int PatternIndex;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBPattern")
		float PatternTime;
	float PatternTimer;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBPattern")
		bool Isonpattern;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBPattern")
		float RadiusRange;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill1_End();
	virtual void Itf_MBSkill1_End_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill2_Start();
	virtual void Itf_MBSkill2_Start_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill2_End();
	virtual void Itf_MBSkill2_End_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill3_End();
	virtual void Itf_MBSkill3_End_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MBSkill3_Start();
	virtual void Itf_MBSkill3_Start_Implementation() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enermy)
	//	class UPrimitiveComponent* MBTriggerCompoent;

	float F1Timer;
	float F2Timer;
	void HpRecover();

	//��ƼŬ �ý���
	/*USphereComponent* SphereTest;
	UParticleSystemComponent* OurParticleSystem;*/

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBPattern")
		bool playParticle;

	UFUNCTION(BlueprintCallable)
		void Skill01();

	UFUNCTION(BlueprintCallable)
		void Skill02();

	UFUNCTION(BlueprintCallable)
		void Skill03();

	UFUNCTION(BlueprintCallable)
		void Skill03End();

private:
	UPROPERTY()
	class USingletonObject *  instance;
};
