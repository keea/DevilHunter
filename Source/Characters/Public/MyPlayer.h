// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Itf_AnimationNotify.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacterClass.h"
#include "CameraDirector.h"
#include "NiagaraSystem.h"
#include "UIText.h"
#include "Itf_EffectNotify.h"
#include "MyPlayer.generated.h"

UENUM()
enum SendMessageType {
	DEATH				UMETA(DisplayName = "death"),
	RESURRECTION		UMETA(DisplayName = "resurrection"),
	ULTIMATE_START		UMETA(DisplayName = "ultimate_start"),
	ULTIMATE_END		UMETA(DisplayName = "ultimate_end"),
};

UENUM()
enum STATE_TYPE {
	//기본 상태
	STATE_DEFAULE		UMETA(DisplayName = "default"),
	//죽음 상태
	STATE_DEATH			UMETA(DisplayName = "death"),
	//부활상태
	STATE_RESURRECTION	UMETA(DisplayName = "resurrection"),
	//스킬 사용 중
	STATE_SKILLING		UMETA(DisplayName = "skilling"),
	//회피 중
	STATE_AVOIDING		UMETA(DisplayName = "avoiding")
};


UCLASS()
class CHARACTERS_API AMyPlayer : public ABasicCharacterClass, public IItf_AnimationNotify, public IItf_EffectNotify
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* OurCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* OurCameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class ULockSpringArmComponent* CameraLockArm;

	//공격 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage * AttackMontage;

	//피격 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* TakeDamageMontages;

	//피격 블레이드 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* TakeDamageBladeMontage;

	//부활 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* ResurrectionMontage;

	//부활 블레이드 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* ResurrectionBladeMontage;

	//넉백 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* KnockbackMontage;

	//넉백 블레이드 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* KnockbackBladeMontage;

	//스턴 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* StunMontage;

	//스턴 블레이드 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* StunBladeMontage;

	//회피 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AvoidMontage;
	//회피 블레이드 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AvoidBladeMontage;

	UPROPERTY()
		class UBasePortion * hpPortion;
	UPROPERTY()
		class UBasePortion * mpPortion;

public:
	// Sets default values for this character's properties
	AMyPlayer();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		class UBoxComponent* MeleeCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
		bool m_bAttack = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PostProcess)
		class UPostProcessComponent* PostProcessComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		class UPointLightComponent* BladePointLightComponent;

	UPROPERTY()
		//콤보상태인가?
		bool m_bCombo;

	UPROPERTY()
		//콤보 공격 인덱스
		int m_iCombo;

	//죽음 상태인지 체크
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		bool m_bNotDeath;

	UPROPERTY()
		//무적 상태인지 체크
		bool m_bInvincibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ultimate)
		//각성 상태인지 체크
		bool m_bUltimate;

	//====== 스탯 설정 부분 ======

	//방어력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float CharDef;

	//최대 MP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float CharMaxMp;

	//현재 MP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float CharMp;

	//크리티컬 확률
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float CriticalRate;

	//크리티컬 공격력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		int CriticalATK;

	//방어 상수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		int CharDEFconst;

	//데미지 투과율
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float CharPenetration;

	//데미지 감소율
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float CharDecrease;


	/* 스탯 값 변경 함수들*/
	UFUNCTION()
		void SetMP(int _mp);


	virtual void SetHP(int _hp) override;

	UFUNCTION()
		int GetMp();

	//====== 스탯 설정 부분 End ======

	//캐릭터 피격 애니메이션 재생중인가?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AnimationState)
		bool m_bPlayTakeDamageAnimation;

	//위험 상태 조건
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatsCondition)
		float DangerousCondition;

	//죽음 후 부활까지 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setting)
		float ResurrectionTime;

	//무적시간 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setting)
		float InvincibilityTime;

	//현재 상태
	//UPROPERTY(EditAnywhere)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		TEnumAsByte<STATE_TYPE> CurrentState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool m_bAttackTimeEnd;
	FTimerHandle m_ProcessingTimer;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void Forward(float amount);

	UFUNCTION()
		void Right(float amount);

	virtual void AddControllerYawInput(float Val) override;
	virtual void AddControllerPitchInput(float Val) override;

	//공격할 때.
	UFUNCTION()
		void AttackStart();

	//공격 애니메이션이 끝났을 때.
	UFUNCTION()
		void AttackEnd();

	UFUNCTION()
		bool GetIsAttack();

	///->대시 관련

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
		TSubclassOf<class UDash> DashClass;

	//대시 관련 설정
	UPROPERTY()
		class UDash * cDash;


	//대시
	UFUNCTION()
		void Dash();

	//대시 이펙트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effect, meta = (AllowPrivateAccess = "true"))
		class UNiagaraSystem* DashEffect;

	//대시 이펙트 생성
	UFUNCTION(BlueprintNativeEvent)
		void ShowDashEffect();
	virtual void ShowDashEffect_Implementation() {};

	//대시 시 모션 블러 생성
	UFUNCTION(BlueprintNativeEvent)
		void SetMotionBlerWeight(float weight);
	virtual void SetMotionBlerWeight_Implementation(float weight) {};

	//대시 시 프렌넬 보이기.
	UFUNCTION(BlueprintNativeEvent)
		void SetDashFresnel(float weight);
	virtual void SetDashFresnel_Implementation(float weight) {};

	//대시 끝내기.
	UFUNCTION(BlueprintNativeEvent)
		void DashEnd();
	virtual void DashEnd_Implementation() {};

	///대시 관련 end <-

	//포스트 프로세싱 설정.

	//모션 블러 머티리얼 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PostProcess, meta = (AllowPrivateAccess = "true"))
		UMaterialInstance * MotionBlur;

	//스크린 데미지 머티리얼 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PostProcess, meta = (AllowPrivateAccess = "true"))
		UMaterialInstance * ScreenDamage;

	//죽음 화면 머티리얼 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PostProcess, meta = (AllowPrivateAccess = "true"))
		UMaterialInstance * ScreenDead;

	//스킬 사용시 주위 어둡게 하는 머티리얼 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PostProcess, meta = (AllowPrivateAccess = "true"))
		UMaterialInstance * DarkScreen;

	UFUNCTION()
		void SetFringe(bool isOn);

	UFUNCTION()
		bool GetAttackTimeEnd();
	UFUNCTION()
		void SetAttackTimeEnd();
	UFUNCTION()
		void DescreaseFringeIntensity();

	///->애니메이션 메시지 받기

	//콤보 리셋 메시지 받기.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_ResetCombo();
	virtual void Itf_ResetCombo_Implementation() override;

	//데미지 피격 끝 메시지 받기.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_EndTakeDamage();
	virtual void Itf_EndTakeDamage_Implementation() override;

	//죽음 애니메이션 끝 메시지 받기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_DeathAnimEnd();
	virtual void Itf_DeathAnimEnd_Implementation() override;

	//부활 애니메이션 끝 메시지 받기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_ResurrectionAnimEnd();
	virtual void Itf_ResurrectionAnimEnd_Implementation() override;

	///애니메이션 메시지 받기 end <-

	//트리거 설정
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//캐릭터의 공격력 반환 함수
	virtual int GetATK() override;

	//캐릭터가 충돌이 일어났을 때.
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category = "AnimationState")
		bool GetPlayTakeDamageAnimation();

	UFUNCTION(BlueprintCallable, Category = "AnimationState")
		bool GetIsDie();

	UFUNCTION(BlueprintCallable, Category = "AnimationState")
		bool GetIsDash();

	//피격 데미지 계산 함수
	UFUNCTION(BlueprintCallable, Category = "AnimationState")
		float HitDamageCalculation(int _atk);

	//부활
	UFUNCTION(BlueprintCallable, Category = "State")
		void Resurrection();

	//무적 시간 끝내기
	UFUNCTION()
		void SetInvincibilityEnd();

	//무적 시간 타이머
	FTimerHandle InvincibilityTimerHandle;
	FTimerHandle ResurrectionTimerHandle;

	//플레이어가 공격을 해서 맞았을 때
	UFUNCTION(BlueprintNativeEvent)
		void TriggerEnterAttack(int damage);
	virtual void TriggerEnterAttack_Implementation(int damage) {};

	void LookUpAtRate(float Rate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY()
		ACameraDirector * pCameraDirector;
	UPROPERTY()
		AActor * aCameraDirector;

	//스킬 매니저 가져오기
	UPROPERTY()
		class ASkillManager * skillManager;

	//죽었다는 메시지 보내기.
	UFUNCTION()
		void SendMessageCamera(SendMessageType msgType);

	//스킬 설정
	UFUNCTION()
		void UseSkill(int type);

	template<int type>
	void UseSkill() { UseSkill(type); }


	//스킬 애니메이션 노티파이 받기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill_Anim")
		void Itf_Skill_Anim(int skillType);
	virtual void Itf_Skill_Anim_Implementation(int skillType) override;

	//스킬 종료 노티파이 받기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
		void Itf_Skill_End(int skillType);
	virtual void Itf_Skill_End_Implementation(int skillType) override;

	//버프형 스킬 붙이기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
		class UParticleSystemComponent* BuffSkillComponent;

	//버프형 스킬 종료
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
		void Itf_Skill_Buff_End();
	virtual void Itf_Skill_Buff_End_Implementation() override;

	//버프형 스킬 시작
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
		void Itf_Skill_Buff_Start();
	virtual void Itf_Skill_Buff_Start_Implementation() override;

	//스턴 애니메이션 종료
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_StunAnimEnd();
	virtual void Itf_StunAnimEnd_Implementation() override;

	//버프 중인가?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		bool isBuff;

	//스킬 애니메이션 종료하는가?
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Skill")
		void Itf_Skill_Anim_End(int skillType);
	virtual void Itf_Skill_Anim_End_Implementation(int skillType) override;

	//위험 상태 true : 1, false : 0
	UFUNCTION(BlueprintNativeEvent)
		void SetDangerousScreen(int weight);
	virtual void SetDangerousScreen_Implementation(int weight) {};

	//죽음 상태 true : 1, false : 0
	UFUNCTION(BlueprintNativeEvent)
		void SetDeadScreen(int weight);
	virtual void SetDeadScreen_Implementation(int weight) {};

	//플레이어 사망시 처리
	UFUNCTION()
		void PlayerDie();

	//물약 관련 설정.
	UFUNCTION()
		void UseHpPortion();

	UFUNCTION()
		void UseMpPortion();

	//스킬 사용시.
	UFUNCTION(BlueprintNativeEvent)
		void SkillStart();
	virtual void SkillStart_Implementation() {};


	//데미지 입었을 때 함수
	UFUNCTION()
		void TakePlayerDamage(float Damage, bool isAniPlay);

	//상태이상 관련 설정
	UPROPERTY()
		class UCondition * cCondition;

	//상태이상 관련 함수 설정
	UFUNCTION()
		void SetCondition(int condition);

	//상태이상 관련 템플릿 함수 설정
	template<typename T>
	void SetCondition(int condition, T value);

	//UI 텍스트 설정
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UiText)
		UUIText * UiText;

	//넉백 애니메이션 재생
	UFUNCTION()
		void PlayKnockbackAnimation();

	//스턴 애니메이션 재생
	UFUNCTION()
		void PlayStunAnimation();

	//이펙트 관련 설정
private:
	//이펙트 정보 가져오기
	class UEffectPlayer * effectPlayer;
public:
	//마나번 파티클 노티파이 받기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Effect")
		void Itf_PlayerManaburnChar();
	virtual void Itf_PlayerManaburnChar_Implementation() override;

	//스턴 파티클 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Itf_Effect")
		class UParticleSystemComponent* PlayerSttifenEffectComponent;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage * DashMontage;


public:
	//검에 관련된 동작
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		class USkeletalMeshComponent * BladeMeshComponent;

	//검 공격에 관한 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponAnimation", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage * BladeAttackMontages;

	UPROPERTY()
		class UAnimInstance * BladeAnimInst;

private:
	UPROPERTY()
		class UAnimInstance * PlayerAnimInst;

public:
	//카메라 얻기
	UFUNCTION()
		class UCameraComponent*	GetOurCamera() const;

private:
	//게임 싱글톤
	UPROPERTY()
		class USingletonObject *  instance;

public:
	//파티클 붙이기.
	UFUNCTION()
		void SpawnEmitterAttached(UParticleSystem * EmitterTemplate, FName AttachPointName, bool bAutoDestroy);

	/* 각성 상태 설정 */

	//각성 상태 시작
	UFUNCTION(BlueprintNativeEvent)
	void StartUltimate(float duration);
	virtual void StartUltimate_Implementation(float duration);
	
	//각성 상태 종료
	UFUNCTION(BlueprintNativeEvent)
	void EndUltimate(); 
	virtual void EndUltimate_Implementation();


	//각성상태관련타이머
	UPROPERTY()
	FTimerHandle UltimateTimerHandle;

	//사망 했을 때 카메라 고정 선택
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	bool isDieCameraFixing;

	//회피 키 눌렸을 때 동작
	UFUNCTION()
	void Avoid();

	//회피 애니메이션 종료 메시지 받기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
	void Itf_Avoid_End();
	virtual void Itf_Avoid_End_Implementation() override;

	//회피 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float avoidCooltime;

	//회피 가능한 상태인가?
	UPROPERTY()
	bool isCanAvoid;

	//회피 관련 타이머
	UPROPERTY()
	FTimerHandle avoidTimerHandle;

	UFUNCTION()
	void EndAvoidCoolTime();

	//몬스터 히트 알람 받기
	UFUNCTION()
	void GetMonsterHitNotice(int type);

	//화면 부수기
	UFUNCTION(BlueprintNativeEvent)
		void BrokenScreenEvent();
	virtual void BrokenScreenEvent_Implementation() {};

	//트레일 시작
	UFUNCTION(BlueprintNativeEvent)
		void TrailStartEvent();
	virtual void TrailStartEvent_Implementation() {};

	//트레일 종료
	UFUNCTION(BlueprintNativeEvent)
		void TrailEndEvent();
	virtual void TrailEndEvent_Implementation() {};

	//레벨 시작 시 호출 1:stage01,2:중간보스,3:최종보스
	UFUNCTION(BlueprintCallable, Category = "Init")
	void GetLevelStart(int level);

	//캐릭터가 공격 받았을 때 블루프린터에 이벤트 보내기
	UFUNCTION(BlueprintNativeEvent)
		void TakeDamage(bool isAniPlay);
	virtual void TakeDamage_Implementation(bool isAniPlay) {};

	//몽타주가 중간에 끝났을 때
	void OnMontageBlendingOut(class UAnimMontage* Montage, bool bInterrupted);

	//회피 이벤트 시작.
	UFUNCTION(BlueprintNativeEvent, Category = "Sound")
	void AvoidEvent();
	virtual void AvoidEvent_Implementation() {};

	//크리티컬 이벤트 시작.
	UFUNCTION(BlueprintNativeEvent, Category = "Sound")
		void CriticalEvent();
	virtual void CriticalEvent_Implementation() {};

private:
	//크리티컬 상태인지 확인
	UPROPERTY()
	bool isCritical;

	//크리티컬 계산
	UFUNCTION()
	int CriticalCalculation();

	//크리티컬 상태인지 확인
	UPROPERTY()
	bool isAttackNotBlock;

public:
	//콘솔 MP 변경
	UFUNCTION(BlueprintCallable, Category = "ConsolCmd")
	virtual void CMDSetMP(int _mp);

	//크리티컬 확률 높이기.(0~100)
	UFUNCTION(BlueprintCallable, Category = "ConsolCmd")
	virtual void CMDSetCrit(float _CriticalRate);

	/* 마지막 대상 전환이 발생한 시간 */
	UPROPERTY(BlueprintReadOnly, Category = "Lock On Camera")
	float LastTargetSwitchTime;

	/* 대상 잠금을 해제하기위한 입력으로 간주되는 마우스 움직임의 허용 오차 */
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float BreakLockMouseDelta;

	/* 플레이어가 카메라 잠금을 해제 한 시간 */
	float BrokeLockTime;

	/* 대상을 전환하기위한 입력으로 간주되는 마우스 움직임의 허용 오차 */
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float TargetSwitchMouseDelta;

	/* 다른 대상 전환이 발생하기 전의 쿨 다운 시간으로, 대상 전환을보다 제어 가능하게 만드는 데 사용. */
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float TargetSwitchMinDelaySeconds;

	/* 플레이어가 카메라를 다시 제어하기 전에 마우스 움직임으로 잠금을 해제 한 후 기다리는 시간입니다. 잠금 해제 후 카메라 오버 스크롤을 방지. */
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float BrokeLockAimingCooldown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lock On Camera")
	float LockonControlRotationRate;;
};

template<typename T>
inline void AMyPlayer::SetCondition(int condition, T value)
{
	cCondition->AddCondition(condition, this, value);
}
