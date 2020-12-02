// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMonsterClass.h"
#include "CoreMinimal.h"
//#include "Itf_AnimationNotify.h"
#include "MyPlayer.h"
#include "GameFramework/Character.h"
#include "StateMachine.h"
#include "CODMon.generated.h"


UCLASS()
class CHARACTERS_API ACODMon : public ABaseMonsterClass//, public IItf_AnimationNotify
{
	GENERATED_BODY()
		StateMachine<ACODMon>*  m_pStateMachine;

		//float TimeSet;
		//FVector Playerpos;//플레이어 위치
		//FVector Monsterpos;//몬스터 위치
		//FVector DirPos;//플레이어 방향 벡터
		//FVector FirPos;//처음 위치

		//bool findChar;//처음에 플레이어를 발견했나
		//float real_Speed;//움직이는 속도
		//bool m_DeadAnim;

		//int pHP;//플레이어 HP

		//float DieDelayTime;
		//bool firstPos;

public:
	// Sets default values for this character's properties
	ACODMon();

	//애니메이션 제어
	//UPROPERTY(BlueprintReadOnly, Category = Animation)
		//bool m_isAttackAnim;

	//UPROPERTY(BlueprintReadOnly, Category = Animation)
	//	bool m_isDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//virtual void ApplyDamageMomentum();
	StateMachine<ACODMon>*  GetFSM()const { return m_pStateMachine; }
	
	void Tracking();
	//void Return();
	void HPRecover();

	//UPROPERTY(EditAnywhere, Category = Character)
	//	ACharacter* PlayerCharacter;//플레이어 캐릭터 찾기

	void MonsterMove();//몬스터 이동
	virtual void Idle() override;

	float DelayTime;
	float Speed;
	float P_dieTime;
	bool attakenMon;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enermy)
		class UPrimitiveComponent* TriggerCompoent;*/

	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//애니메이션 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* MeleeAttackMontage;

	//몽타주들
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	//	TArray<UAnimMontage * >AnimMontages;

	/*UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MonATK();
	virtual void Itf_MonATK_Implementation() override;*/

	bool GetIsPlayerDie();

	bool GetIsMonsterDie();

	float GetIsMonSpeed();
	void SetIsMonSpeed(float Speed);

	bool GetIsFindChar();
	void SetIsFindChar(bool findchar);

	bool GetIsAttaken();
};
