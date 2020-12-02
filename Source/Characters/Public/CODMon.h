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
		//FVector Playerpos;//�÷��̾� ��ġ
		//FVector Monsterpos;//���� ��ġ
		//FVector DirPos;//�÷��̾� ���� ����
		//FVector FirPos;//ó�� ��ġ

		//bool findChar;//ó���� �÷��̾ �߰��߳�
		//float real_Speed;//�����̴� �ӵ�
		//bool m_DeadAnim;

		//int pHP;//�÷��̾� HP

		//float DieDelayTime;
		//bool firstPos;

public:
	// Sets default values for this character's properties
	ACODMon();

	//�ִϸ��̼� ����
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
	//	ACharacter* PlayerCharacter;//�÷��̾� ĳ���� ã��

	void MonsterMove();//���� �̵�
	virtual void Idle() override;

	float DelayTime;
	float Speed;
	float P_dieTime;
	bool attakenMon;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enermy)
		class UPrimitiveComponent* TriggerCompoent;*/

	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//�ִϸ��̼� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* MeleeAttackMontage;

	//��Ÿ�ֵ�
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
