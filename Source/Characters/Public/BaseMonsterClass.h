// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacterClass.h"
#include "Itf_AnimationNotify.h"
#include "Particles/ParticleSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BaseMonsterClass.generated.h"


UENUM(BlueprintType)
enum class EEnemyMovementStatus : uint8
{
	EMS_IDLE UMETA(DisplayName = "Idle"),
	EMS_CHASE UMETA(DisplayName = "Chase"),
	EMS_ATTACK_0 UMETA(DisplayName = "Attacking1"),
	EMS_ATTACK_1 UMETA(DisplayName = "Attacking2"),
	EMS_ATTACK_2 UMETA(DisplayName = "Attacking3"),
	EMS_ATTACK_3 UMETA(DisplayName = "Attacking4"),
	EMS_ATTACK_4 UMETA(DisplayName = "Attacking5"),
	EMS_ATTACK_5 UMETA(DisplayName = "Attacking6"),

	EMS_FAINT UMETA(DisplayName = "Faint"),
	EMS_DEAD UMETA(DisplayName = "Dead"),

	EMS_MAX UMETA(DisplayName = "DefaultMax")
};


UCLASS()
class CHARACTERS_API ABaseMonsterClass : public ABasicCharacterClass, public IItf_AnimationNotify
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	EEnemyMovementStatus EnemyMovementStatus;

	FORCEINLINE void SetEnemyMovementStatus(EEnemyMovementStatus Status) {
		EnemyMovementStatus = Status;
	}

	FORCEINLINE EEnemyMovementStatus GetEnemyMovementStatus() { return EnemyMovementStatus; }

	float TimeSet;
	FVector Playerpos;//플레이어 위치
	FVector Monsterpos;//몬스터 위치
	FVector DirPos;//플레이어 방향 벡터


	bool findChar;//처음에 플레이어를 발견했나
	float real_Speed;//움직이는 속도
	bool m_DeadAnim;

	int pHP;//플레이어 HP
	float dircheck;

	float DieDelayTime;
	bool firstPos;
	float DeadTime;
	float Speed;
	float P_dieTime;

	float faintCount;
	float d_transmittance;//데미지 투과율
	float m_isAttackTime;

	int Takedamage;

public:
	// Sets default values for this character's properties
	ABaseMonsterClass();

	//애니메이션 제어
	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isAttackAnim;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isAttack;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Position)
		float m_isAttackTimer;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isHit;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isDead;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isPDead;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isFindChar;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		int mode;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		float DelayTime;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isPlayPattern;//패턴 플레이

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Position)
	FVector FirPos;//처음 위치

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Position)
		float p_dieDelay;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isFaint;//기절

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		float m_isFaintTime;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		float m_isFaintDelayTime;//기절 시간

		//스킬 발동
	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBSkill")
		bool m_OnSkill;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage * >AnimMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UAnimMontage* CombatMontage;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enermy)
		class UPrimitiveComponent* TriggerCompoent;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		virtual void Chase();

	UFUNCTION()
		virtual void Return();

	UFUNCTION()
		virtual void Idle();

	UFUNCTION()
		virtual void Dead();
	UFUNCTION()
		bool DirCheck(float limit);

	UFUNCTION()
		virtual void MonsterTakeDamage(int atk_damage);//보스들. 받은 데미지 받아옴

	UFUNCTION()
		virtual void PlayerTakeDamage(int atk_damage);

	UFUNCTION()
		virtual bool GetIsAttack();

	UFUNCTION()
		virtual void SetIsAttack(bool attack);

	UFUNCTION()
		virtual int GetTakeDamage();

	UFUNCTION()
		virtual void SetTakeDamage(int damage);

	
	UPROPERTY(EditAnywhere, Category = Character)
		ACharacter* PlayerCharacter;//플레이어 캐릭터 찾기

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MonATK();
	virtual void Itf_MonATK_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MonATK_START();
	virtual void Itf_MonATK_START_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_Skill_Damage(float damage);
	virtual void Itf_Skill_Damage_Implementation(float damage) override;

	UFUNCTION(BlueprintCallable)
		void AttackStart();

	UFUNCTION(BlueprintCallable)
		void AttackEnd();

	UFUNCTION(BlueprintCallable)
		void DeathEnd();

	UFUNCTION(BlueprintCallable)
		void SkillStart();

	UFUNCTION(BlueprintCallable)
		void SkillEnd();
};
