// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "CODMon.h"
#include "SkillManager.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Particles/ParticleSystemComponent.h"
#include "HpPortion.h"
#include "MpPortion.h"
#include "Dash.h"
#include "Condition.h"
#include "UIText.h"
#include "MyGameInstance.h"
#include "EffectPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "SingletonObject.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/PointLightComponent.h"
#include "Math/UnrealMathUtility.h"
#include "LockSpringArmComponent.h"
#include "TargetComponent.h"
#include "Engine/Engine.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//캐릭터 설정//
	//캐릭터가 카메라의 회전을 따라서 회전하지 않도록 한다.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	BaseLookUpRate = 45.f;

	//검 매시 컴포넌트
	BladeMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BladeMeshComponent"));

	//포인트 라이트 컴포넌트(스킬3 사용시 빛나게 함)
	BladePointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("BladePointLightComponent"));
	BladePointLightComponent->SetupAttachment(BladeMeshComponent);

	//스프링암 컴포넌트 생성.
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->TargetArmLength = 300.0f;
	OurCameraSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	CameraLockArm = CreateDefaultSubobject<ULockSpringArmComponent>(TEXT("CameraLockArm"));
	CameraLockArm->SetupAttachment(RootComponent);
	CameraLockArm->TargetArmLength = 300.0f;
	CameraLockArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(CameraLockArm, USpringArmComponent::SocketName);
	OurCamera->bUsePawnControlRotation = false;

	//카메라 락 설정
	LockonControlRotationRate = 10.0f;
	BreakLockMouseDelta = 10.0f;
	TargetSwitchMouseDelta = 3.f;
	TargetSwitchMinDelaySeconds = .5f;
	BrokeLockAimingCooldown = .5f;

	//캐릭터 공격 설정.
	MeleeCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeCollisionBox"));
	MeleeCollisionBox->SetupAttachment(BladeMeshComponent);
	MeleeCollisionBox->SetCollisionProfileName("Weapon");
	MeleeCollisionBox->SetHiddenInGame(false);

	BuffSkillComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BuffSkill"));
	BuffSkillComponent->SetupAttachment(BladeMeshComponent);

	//포스트 프로세스 설정.
	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcessComponent->SetupAttachment(RootComponent);

	//스턴 이펙트 컴포넌트 설정.
	PlayerSttifenEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlayerSttifenParticleSystem"));
	m_bAttackTimeEnd = true;

	m_bCombo = false;
	m_iCombo = 0;

	//피격받았지 않음므로 false로 지정한다.
	m_bPlayTakeDamageAnimation = false;

	/* 스탯 초기화 */
	//플레이어의 MP를 최대 MP로 변환시킨다.
	CharMp = CharMaxMp;

	//위험상태 조건은 HP의 30%로 초기화한다.
	DangerousCondition = 30.0f;

	//방어 상수
	CharDEFconst = 100;

	//데미지 투과율
	CharPenetration = 0.678f;

	//데미지 감소율
	CharDecrease = 0.33f;
	/* 스탯 초기화 end*/

	m_bNotDeath = true;
	m_bInvincibility = false;
	InvincibilityTime = 2.0f;

	//각성 상태 초기화.
	m_bUltimate = false;

	//현재 상태 정의 - 기본상태로
	CurrentState = STATE_TYPE::STATE_DEFAULE;

	//버프초기화
	isBuff = false;

	//싱글톤 오브젝트 설정
	if (GEngine != NULL)
		instance = Cast < USingletonObject >(GEngine->GameSingleton);

	//UI 텍스트 설정하기
	UiText = CreateDefaultSubobject <UUIText>(TEXT("UiText"));
	UiText->SetInit(this);
	if (UiText == NULL)
		UE_LOG(LogTemp, Log, TEXT("UiText Not found!"));

	//크리티컬 상태가 아니다
	isCritical = false;

	isAttackNotBlock = true;

	//회피를 사용할 수 있다.
	isCanAvoid = true;
}

void AMyPlayer::SetMP(int _mp)
{
	//mp가 MaxHP 넘지 않도록 막기.
	if (_mp > CharMaxMp)
	{
		CharMp = CharMaxMp;
		return;
	}
	CharMp = _mp;

	//ui에 MP의 변화를 알린다.
	UiText->MPCheck();
}

void AMyPlayer::SetHP(int _hp)
{
	//HP 값 변경.
	Super::SetHP(_hp);

	//HP 값 변경을 UI에게 알림.
	UiText->HPCheck();
}

int AMyPlayer::GetMp()
{
	return CharMp;
}


// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	//현재 상태 정의 - 기본상태로
	CurrentState = STATE_TYPE::STATE_DEFAULE;

	//플레이어의 MP를 최대 MP로 변환시킨다.
	CharMp = CharMaxMp;

	//SetMotionBlerWeight(motionBlurWeight);
	//attach collision components to sockets based on transformation definnate

	//플레이어 AnimInstance
	PlayerAnimInst = GetMesh()->GetAnimInstance();

	//검 AnimInstance
	BladeAnimInst = BladeMeshComponent->GetAnimInstance();

	const FAttachmentTransformRules AttackmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	const FAttachmentTransformRules AttackmentBuffRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	const FAttachmentTransformRules AttackmentBladeRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	//검 붙이기
	BladeMeshComponent->AttachToComponent(GetMesh(), AttackmentBladeRules);
	MeleeCollisionBox->AttachToComponent(BladeMeshComponent, AttackmentBladeRules, "P_BN_Blade");
	BuffSkillComponent->AttachToComponent(BladeMeshComponent, AttackmentBladeRules, "P_BN_Blade");

	//포인트라이트 컴포넌트 붙이기.
	BladePointLightComponent->AttachToComponent(BladeMeshComponent, AttackmentBladeRules, "P_BN_Blade");

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnOverlapBegin);
	const FAttachmentTransformRules AttackmentPlayerReviveRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);

	//스턴 이펙트 컴포넌트 설정
	PlayerSttifenEffectComponent->AttachToComponent(GetMesh(), AttackmentPlayerReviveRules, "FX_Heart_Emote");

	//hp 물약 설정
	hpPortion = NewObject<UHpPortion>(this);
	//mp 물약 설정
	mpPortion = NewObject<UMpPortion>(this);

	//대시 클래스 설정
	cDash = NewObject<UDash>(this, *DashClass);

	cCondition = NewObject<UCondition>(this);

	if (UiText == NULL) {
		UiText = NewObject<UUIText>(this);
		UiText->SetInit(this);
	}

	//이펙트 가져오기 설정.
	//effectPlayer = GetWorld()->GetGameInstance<UMyGameInstance>()->EffectClass.GetDefaultObject();
	instance = Cast < USingletonObject >(GEngine->GameSingleton);

	//몬스터 hit 델리게이트 등록
	if (GetWorld()->GetGameInstance<UMyGameInstance>() != NULL) {
		GetWorld()->GetGameInstance<UMyGameInstance>()->Fuc_HitMonster.BindUFunction(this, FName("GetMonsterHitNotice"));
	}

	for (TActorIterator<ASkillManager> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		skillManager = Cast<ASkillManager>(*ActorItr);
		if (skillManager) {
			UE_LOG(LogTemp, Log, TEXT("skillManager found!"));
			break;
		}
	}

	for (TActorIterator<ACameraDirector> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		pCameraDirector = Cast<ACameraDirector>(*ActorItr);
		if (pCameraDirector)
		{
			UE_LOG(LogTemp, Log, TEXT("APrimaryPlayerController: GetAreaLightingController(): controller found!"));
			aCameraDirector = Cast<AActor>(*ActorItr);
			return;
		}
	}
}


// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	if (!(HP <= (MaxHP * DangerousCondition) / 100)) 
	{
		SetDangerousScreen(0);
	}

	Super::Tick(DeltaTime);

	if (CameraLockArm->IsCameraLockedToTarget())
	{
		// Vector from player to target
		FVector TargetVect = CameraLockArm->CameraTarget->GetComponentLocation() - CameraLockArm->GetComponentLocation();
		FRotator TargetRot = TargetVect.GetSafeNormal().Rotation();
		FRotator CurrentRot = GetControlRotation();
		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, LockonControlRotationRate);

		// Update control rotation to face target
		GetController()->SetControlRotation(NewRot);
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AMyPlayer::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMyPlayer::Right);
	PlayerInputComponent->BindAxis("Turn", this, &AMyPlayer::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookUp", this, &AMyPlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyPlayer::LookUpAtRate);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMyPlayer::AttackStart);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMyPlayer::Dash);

	PlayerInputComponent->BindAction("Skill1", IE_Pressed, this, &AMyPlayer::UseSkill<0>);
	PlayerInputComponent->BindAction("Skill2", IE_Pressed, this, &AMyPlayer::UseSkill<1>);
	PlayerInputComponent->BindAction("Skill3", IE_Pressed, this, &AMyPlayer::UseSkill<2>);
	PlayerInputComponent->BindAction("Skill4", IE_Pressed, this, &AMyPlayer::UseSkill<3>);
	PlayerInputComponent->BindAction("Skill5", IE_Pressed, this, &AMyPlayer::UseSkill<4>);

	PlayerInputComponent->BindAction("HpPortion", IE_Pressed, this, &AMyPlayer::UseHpPortion);
	PlayerInputComponent->BindAction("MpPortion", IE_Pressed, this, &AMyPlayer::UseMpPortion);

	//회피하기
	PlayerInputComponent->BindAction("Avoid", IE_Pressed, this, &AMyPlayer::Avoid);

	//카메라 락
	PlayerInputComponent->BindAction("ToggleSoftLock", IE_Pressed, CameraLockArm, &ULockSpringArmComponent::ToggleSoftLock);
}

//위, 아래키를 눌렸을 때의 동작
void AMyPlayer::Forward(float amount)
{
	//현재 상태가 기본상태가 아니라면
	if (CurrentState != STATE_TYPE::STATE_DEFAULE)
		return;

	if (!isAttackNotBlock)
		return;

	if ((Controller != NULL) && (amount != 0.0f))
	{
		// find out which way is forward
		//const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Rotation = CameraLockArm->CameraTarget == nullptr ? Controller->GetControlRotation() : (CameraLockArm->CameraTarget->GetOwner()->GetActorLocation() - GetActorLocation()).GetSafeNormal().Rotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, amount);
		m_bCombo = false;
	}
}

//왼쪽, 오른쪽키를 눌렸을 때의 동작
void AMyPlayer::Right(float amount)
{
	//현재 상태가 기본상태가 아니라면
	if (CurrentState != STATE_TYPE::STATE_DEFAULE)
	{
		return;
	}


	if (!isAttackNotBlock)
		return;

	if ((Controller != NULL) && (amount != 0.0f))
	{
		// find out which way is right
		//const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Rotation = CameraLockArm->CameraTarget == nullptr ? Controller->GetControlRotation() : (CameraLockArm->CameraTarget->GetOwner()->GetActorLocation() - GetActorLocation()).GetSafeNormal().Rotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, amount);
		m_bCombo = false;
	}
}

void AMyPlayer::AddControllerYawInput(float Val)
{
	//현재 상태가 죽음 상태이고 고정 카메라 상태라면
	if (isDieCameraFixing && GetIsDie())
	{
		//카메라 움직이는 것을 막는다.
		return;
	}


	float TimeSinceLastTargetSwitch = GetWorld()->GetRealTimeSeconds() - LastTargetSwitchTime;

	if (CameraLockArm->IsCameraLockedToTarget())
	{
		// Should break soft-lock?
		if (CameraLockArm->bUseSoftLock && FMath::Abs(Val) > BreakLockMouseDelta)
		{
			CameraLockArm->BreakTargetLock();
			BrokeLockTime = GetWorld()->GetRealTimeSeconds();
			CameraLockArm->bSoftlockRequiresReset = true;
		}
		// Should try switch target?
		else if (FMath::Abs(Val) > TargetSwitchMouseDelta
			&& TimeSinceLastTargetSwitch > TargetSwitchMinDelaySeconds)	// Prevent switching multiple times using a single movement
		{
			if (Val < 0)
				CameraLockArm->SwitchTarget(EDirection::Left);
			else
				CameraLockArm->SwitchTarget(EDirection::Right);

			LastTargetSwitchTime = GetWorld()->GetRealTimeSeconds();
		}
	}
	else
	{
		// If camera lock was recently broken by a large mouse delta, allow a cooldown time to prevent erratic camera movement
		bool bRecentlyBrokeLock = (GetWorld()->GetRealTimeSeconds() - BrokeLockTime) < BrokeLockAimingCooldown;
		if (!bRecentlyBrokeLock)
			Super::AddControllerYawInput(Val);
	}
}

void AMyPlayer::AddControllerPitchInput(float Val)
{
	//스타트 플레이스에 작동하도록.
	if (GetWorld()->GetName() == FString("StartPlace")) {
		Super::AddControllerPitchInput(Val);
	}
	/*else {
		if (!CameraLockArm->IsCameraLockedToTarget())
			Super::AddControllerPitchInput(Val);
	}*/
}

void AMyPlayer::LookUpAtRate(float Rate)
{
	if (GetWorld()->GetName() == FString("StartPlace")) {
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
	else 
	{
		// 속도 정보에서이 프레임에 대한 델타 계산
		if (!CameraLockArm->IsCameraLockedToTarget())
			AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMyPlayer::SendMessageCamera(SendMessageType msgType)
{
	//해당 클래스에 해당 Interface클래스가 존재하는지 확인
	if (pCameraDirector->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true) {
		//함수 호출
		if (msgType == SendMessageType::DEATH) {
			IItf_AnimationNotify::Execute_Itf_PlayerDie(aCameraDirector);
			return;
		}
		else if (msgType == SendMessageType::ULTIMATE_START) {
			IItf_AnimationNotify::Execute_Itf_Skill_Ultimate_Start(aCameraDirector);
			return;
		}
		else if (msgType == SendMessageType::ULTIMATE_END) {
			IItf_AnimationNotify::Execute_Itf_Skill_Ultimate_End(aCameraDirector);
			return;
		}
		else if (msgType == SendMessageType::RESURRECTION) {
			IItf_AnimationNotify::Execute_Itf_PlayerResurrection(aCameraDirector);
			return;
		}
	}
}

void AMyPlayer::UseSkill(int type)
{
	//현재 상태가 기본상태가 아니라면
	if (CurrentState != STATE_TYPE::STATE_DEFAULE)
		return;

	if (!isAttackNotBlock)
		return;


	if (skillManager) {
		bool isSkillSuccess = skillManager->UseSkill(this, type);
		if (isSkillSuccess)
		{
			UE_LOG(LogTemp, Log, TEXT("UseSkill"));
			SkillStart();
		}
		else
		{
			UiText->NotSkillCheck();
		}
	}
}

void AMyPlayer::Itf_Skill_Anim_Implementation(int skillType)
{
	UE_LOG(LogTemp, Log, TEXT("Itf_Skill_Anim_Implementation"));
	if (skillManager->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true)
	{
		IItf_AnimationNotify::Execute_Itf_Skill_Anim(skillManager, skillType);
	}
}

void AMyPlayer::Itf_Skill_End_Implementation(int skillType)
{
	UE_LOG(LogTemp, Log, TEXT("Itf_Skill_End_Implementation"));
	if (skillManager->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true) {
		if (skillType == 4 || skillType == 3)
			SendMessageCamera(SendMessageType::ULTIMATE_END);

		if (skillType == 3)
		{
			UE_LOG(LogTemp, Log, TEXT("Itf_Skill_End_Implementation Skill04"));
			//스킬 종료 후 파티클 재생.
			SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_skill4_spark_body), "P_Bip", true);
		}

		if (skillType == 4)
		{
			UE_LOG(LogTemp, Log, TEXT("Itf_Skill_End_Implementation Skill05"));
			//스킬 종료 후 파티클 재생.
			SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_ult_char), "P_Bip", true);
		}

		IItf_AnimationNotify::Execute_Itf_Skill_End(skillManager, skillType);
	}
}

void AMyPlayer::Itf_Skill_Buff_End_Implementation()
{
	isBuff = false;
}

void AMyPlayer::Itf_Skill_Buff_Start_Implementation()
{
	isBuff = true;
}

//스턴 애니메이션 종료
void AMyPlayer::Itf_StunAnimEnd_Implementation()
{
	isAttackNotBlock = true;

	//스턴 상태이상 제거
	cCondition->DeleteCondition(STAT_STUN);
}



void AMyPlayer::Itf_Skill_Anim_End_Implementation(int skillType)
{
	UE_LOG(LogTemp, Log, TEXT("Itf_Skill_Anim_End_Implementation"));
	m_bAttack = false; //공격 상태를 false로 한다.

	//상태를 원래 상태로 바꾼다.
	CurrentState = STATE_TYPE::STATE_DEFAULE;
	//무적상태 해제
	m_bInvincibility = false;

	if (skillManager->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true) {
		if (skillType == 4 || skillType == 3)
			SendMessageCamera(SendMessageType::ULTIMATE_END);

		if (skillType == 3)
		{
			UE_LOG(LogTemp, Log, TEXT("Itf_Skill_End_Implementation Skill04"));
			//스킬 종료 후 파티클 재생.
			SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_skill4_spark_body), "P_Bip", true);
		}

		if (skillType == 4)
		{
			UE_LOG(LogTemp, Log, TEXT("Itf_Skill_End_Implementation Skill05"));
			//스킬 종료 후 파티클 재생.
			SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_ult_char), "P_Bip", true);
		}

		IItf_AnimationNotify::Execute_Itf_Skill_End(skillManager, skillType);
	}
}

void AMyPlayer::PlayerDie()
{
	m_bNotDeath = false;

	//슬로우 모션 추가
	GetWorld()->GetGameInstance<UMyGameInstance>()->StartSlowMotion();

	//죽을 때 데미지 화면을 없앤다.
	SetDangerousScreen(0);

	//죽음 화면을 나타낸다.
	SetDeadScreen(1);

	SendMessageCamera(SendMessageType::DEATH);
	CurrentState = STATE_TYPE::STATE_DEATH;

	//포션 사망 처리한다.
	hpPortion->PlayerDie();
	mpPortion->PlayerDie();

	//상태 이상을 초기화 한다.
	cCondition->InitCondition();

	//콤보, 최대 콤보를 초기화 한다.
	GetWorld()->GetGameInstance<UMyGameInstance>()->InitCombos();
}

void AMyPlayer::UseHpPortion()
{
	//스타트 플레이스라면 못하게한다.
	if (GetWorld()->GetName() == FString("StartPlace")) {
		return;
	}

	//현재 상태가 기본상태가 아니라면
	if (CurrentState != STATE_TYPE::STATE_DEFAULE)
		return;

	if (hpPortion != NULL)
	{
		bool isSucess = hpPortion->Execute(this);
		//성공 할 경우 HP 포션 이펙트를 보여준다.
		if (isSucess)
		{
			SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_potionHP), "P_Root", true);
		}
	}
}

void AMyPlayer::UseMpPortion()
{
	//스타트 플레이스라면 못하게한다.
	if (GetWorld()->GetName() == FString("StartPlace")) {
		return;
	}

	//현재 상태가 기본상태가 아니라면
	if (CurrentState != STATE_TYPE::STATE_DEFAULE)
		return;

	if (mpPortion != NULL)
	{
		mpPortion->Execute(this);

		bool isSucess = hpPortion->Execute(this);
		//성공 할 경우 MP 포션 이펙트를 보여준다.
		if (isSucess)
		{
			SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_potionMP), "P_Root", true);
		}
	}
}

void AMyPlayer::TakePlayerDamage(float Damage, bool isAniPlay)
{
	if (m_bInvincibility)
		return;

	if (isAniPlay) {
		//플레이어가 피격 애니메이션 재생 중이 아니라면
		if (!m_bPlayTakeDamageAnimation)
		{
			//공격 상태를 초기화 시켜준다.
			m_bAttack = false;
			m_iCombo = 0;

			//피격 애니메이션 재생
			float check = PlayAnimMontage(TakeDamageMontages, 1.f, FName("Default"));
			if (KnockbackBladeMontage != NULL)
				BladeAnimInst->Montage_Play(TakeDamageBladeMontage);

			//애니메이션 델리게이트 등록
			FOnMontageBlendingOutStarted MontageBlendOutDelegate;
			MontageBlendOutDelegate.BindUObject(this, &AMyPlayer::OnMontageBlendingOut);
			PlayerAnimInst->Montage_SetBlendingOutDelegate(MontageBlendOutDelegate);

			//피격 애니메이션 재생 상태를 true로 바꾼다.
			m_bPlayTakeDamageAnimation = true;
			//몽타주 재생이 안된다면
			if (check == 0) {
				m_bPlayTakeDamageAnimation = false;
			}
		}
	}

	//피격 이벤트 피 이펙트 랜덤값 가져오기
	int randValue = FMath::RandRange(0, 3);

	//피격 이펙트 보여주기
	SpawnEmitterAttached(instance->GetEffect((EEFFECTS)((int)EEFFECTS::blood1 + randValue)), "P_Bip-RUpArmTwist", true);

	//데미지 연출해달라고 알림.
	TakeDamage(isAniPlay);

	//HP 감소
	SetHP(HP - Damage);

	TriggerEnterAttack((int)Damage);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("HP :: %f"), HP));

	//사망 : 체력이 0이 되어 현재 위치한 자리에서 사망 : 사망 애니메이션 보여준다.
	if (HP <= 0) {

		PlayerDie();

		return; //사망한 후 더 이상 처리할 필요가 없기 때문에
	}

	//위험 : 플레이어의 HP가 30% 이하 일 시 발생 
	if (HP <= (MaxHP * DangerousCondition) / 100) {
		SetDangerousScreen(1);
		// 체력이 얼마 남지 않았습니다. UI 띄우기
		UE_LOG(LogTemp, Log, TEXT("HP가 얼마 남지 않았습니다!!!"));
	}
}

void AMyPlayer::SetCondition(int condition)
{
	cCondition->AddCondition(condition, this);
}

void AMyPlayer::PlayKnockbackAnimation()
{
	//넉백 애니메이션을 재생시킨다.
	PlayAnimMontage(KnockbackMontage, 1.0f, FName("Default"));
	if (KnockbackBladeMontage != NULL)
		BladeAnimInst->Montage_Play(KnockbackBladeMontage);
}

void AMyPlayer::PlayStunAnimation()
{
	PlayAnimMontage(StunMontage, 1.0f, FName("Default"));
	if (StunBladeMontage != NULL)
		BladeAnimInst->Montage_Play(StunBladeMontage);
}

void AMyPlayer::Itf_PlayerManaburnChar_Implementation()
{
	//이펙트를 지정한다.
	//PlayerManaburnCharComponent->SetTemplate(effectPlayer->PlayerManaburnChar);
	UE_LOG(LogTemp, Log, TEXT("player_manaburn_char"));

	//이펙트 실행
	SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_manaburn_char), "P_Bip-Pelvis", true);
}

UCameraComponent * AMyPlayer::GetOurCamera() const
{
	return OurCamera;
}

void AMyPlayer::SpawnEmitterAttached(UParticleSystem * EmitterTemplate, FName AttachPointName, bool bAutoDestroy)
{
	UGameplayStatics::SpawnEmitterAttached(EmitterTemplate,
		GetMesh(), AttachPointName,
		FVector(0, 0, 0), FRotator(0, 0, 0),
		EAttachLocation::KeepRelativeOffset, true);
}

//각성상태 시작
void AMyPlayer::StartUltimate_Implementation(float duration)
{
	UE_LOG(LogTemp, Log, TEXT("Invincibility ON"));
	//각성 상태로 돌입한다.
	m_bUltimate = true;
	//일정 시간 후 무적상태가 종료되게 하기 위해 타이머를 실행한다.
	GetWorldTimerManager().SetTimer(UltimateTimerHandle, this, &AMyPlayer::EndUltimate, duration, false);
}

//각성상태종료
void AMyPlayer::EndUltimate_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Invincibility OFF"));
	//각성 상태로 해제한다.
	m_bUltimate = false;
	//타이머 종료
	GetWorldTimerManager().ClearTimer(UltimateTimerHandle);
}

void AMyPlayer::Avoid()
{
	//스타트 플레이스라면 못하게한다.
	if (GetWorld()->GetName() == FString("StartPlace")) {
		return;
	}

	//만약 스킬 사용중이라면 회피를 못하게 막는다.
	if (CurrentState == STATE_TYPE::STATE_SKILLING)
		return;

	if (!isCanAvoid)
		return;

	//공격 상태를 취소한다.
	m_bAttack = false;
	
	//현재 상태를 회피 상태로 바꾼다.
	CurrentState = STATE_TYPE::STATE_AVOIDING;

	//트레일을 시작한다.
	TrailStartEvent();

	//회피 이벤트 시작한다.
	AvoidEvent();
	UiText->Pvasion();

	//회피 몽타주를 재생한다.
	float checkPlayMontage = PlayAnimMontage(AvoidMontage, 1.f, FName("Default"));
	if (AvoidBladeMontage != NULL)
	{
		BladeAnimInst->Montage_Play(AvoidBladeMontage);
	}

	//애니메이션 델리게이트 등록
	FOnMontageBlendingOutStarted MontageBlendOutDelegate;
	MontageBlendOutDelegate.BindUObject(this, &AMyPlayer::OnMontageBlendingOut);
	PlayerAnimInst->Montage_SetBlendingOutDelegate(MontageBlendOutDelegate);

	//회피를 못사용하게 막는다.
	isCanAvoid = false;
	//일정 시간 후 회피 사용할 수 있게 한다.
	GetWorldTimerManager().SetTimer(avoidTimerHandle, this, &AMyPlayer::EndAvoidCoolTime, avoidCooltime, false);
}

void AMyPlayer::Itf_Avoid_End_Implementation()
{
	//트레일을 종료한다.
	TrailEndEvent();
	//디폴트 상태로 바꾼다.
	CurrentState = STATE_TYPE::STATE_DEFAULE;
}

void AMyPlayer::EndAvoidCoolTime()
{
	//회피를 사용할 수 있는 상태로 바꾼다.
	isCanAvoid = true;
}

void AMyPlayer::GetMonsterHitNotice(int type)
{
	//중간보스 최종보스 경우
	if (type == 2 || type == 3)
	{
		if (m_iCombo == 2 && isCritical) //3번째 타격이고, 크리티컬 떴을 때
		{
			BrokenScreenEvent();
		}
	}
	isCritical = false;
}

//레벨 시작 시 호출 1:stage01,2:중간보스,3:최종보스
void AMyPlayer::GetLevelStart(int level)
{
	switch (level)
	{
	case 2:
		OurCamera->FieldOfView = 100.0f;
		{
			OurCameraSpringArm->TargetArmLength = 500.0f;
			OurCameraSpringArm->TargetOffset.Z = 200.0f;
		
			CameraLockArm->TargetArmLength = 500.0f;
			CameraLockArm->TargetOffset.Z = 200.0f;
		}
		break;
	case 3:
		OurCamera->FieldOfView = 100.0f;
		{
			OurCameraSpringArm->TargetArmLength = 500.0f;
			OurCameraSpringArm->TargetOffset.Z = 200.0f;

			CameraLockArm->TargetArmLength = 500.0f;
			CameraLockArm->TargetOffset.Z = 200.0f;
		}
		break;
	}
}

void AMyPlayer::OnMontageBlendingOut(UAnimMontage * Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Log, TEXT("OnMontageBlendingOut"));
	if (bInterrupted) //중간에 다른 애니메이션으로 바뀌었다면
	{
		//회피 몽타주가
		if (Montage == AvoidMontage) 
		{
			UE_LOG(LogTemp, Log, TEXT("OnMontageBlendingOut AvoidMontage"));

			//트레일을 종료한다.
			TrailEndEvent();
			//디폴트 상태로 바꾼다.
			CurrentState = STATE_TYPE::STATE_DEFAULE;
		}
		else if (Montage == TakeDamageMontages) {
			UE_LOG(LogTemp, Log, TEXT("OnMontageBlendingOut TakeDamageMontages"));
			
			//피격 애니메이션이 중간에 중지되었으니 false로 바꿔준다.
			m_bPlayTakeDamageAnimation = false;
			isAttackNotBlock = true;
		}
	}
}

//크리티컬 계산
int AMyPlayer::CriticalCalculation()
{
	//버스스킬 사용시 크리티컬 증가폭
	int buffUpCritical = 10 * isBuff; //만약 버프가 false라면 0이다.

	//크리티컬 계산 추가
	int radomValue = FMath::RandRange(0, 100);
	//크리티컬 발생 조건
	if (radomValue <= CriticalRate + buffUpCritical)
	{
		isCritical = true;
		UE_LOG(LogTemp, Log, TEXT("CriticalCalculation"));
		//크리티컬 이벤트 실행
		CriticalEvent();
		//이펙트 실행
		SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_critical1), "P_Bip-Head_effect", true);
		return (CriticalATK / 100.0f);
	}

	return 0;
}

void AMyPlayer::CMDSetMP(int _mp)
{
	CharMaxMp = _mp; //최대 mp 변경
	CharMp = _mp; //현재 mp 변경
}

void AMyPlayer::CMDSetCrit(float _CriticalRate)
{
	CriticalRate = _CriticalRate;
}


void AMyPlayer::AttackStart()
{
	isCritical = false;
	//현재 상태가 기본상태가 아니라면
	if (CurrentState != STATE_TYPE::STATE_DEFAULE)
		return;

	UE_LOG(LogTemp, Log, TEXT("AttackStart : STATE_TYPE::STATE_DEFAULE"));

	if (!isAttackNotBlock)
		return;

	UE_LOG(LogTemp, Log, TEXT("AttackStart : isAttackNotBlock"));

	//attack이 true 일 때 클릭하면 
	if (m_bAttack)
	{
		//콤보상태를 true한다.
		m_bCombo = true;
		UE_LOG(LogTemp, Log, TEXT("AttackStart : m_bAttack"));
	}
	else
	{//그렇지 않을 경우 
		UE_LOG(LogTemp, Log, TEXT("AttackStart : !m_bAttack"));
		//m_bAttack 상태를 true 바꾸고, 콤보도 0으로 바꾸고
		m_bAttack = true; m_iCombo = 0;

		//애니메이션을 재생시킨다.
		UE_LOG(LogTemp, Log, TEXT("AttackStart000"));
		if (BladeAnimInst)
		{
			//몽타주 재생.
			PlayAnimMontage(AttackMontage, 1.f, FName(*FString::Printf(TEXT("attack%d"), m_iCombo)));
			BladeAnimInst->Montage_JumpToSection(FName(*FString::Printf(TEXT("attack%d"), m_iCombo)), BladeAttackMontages);
			BladeAnimInst->Montage_Play(BladeAttackMontages, 1.f);
			UE_LOG(LogTemp, Log, TEXT("AttackStart111"));
		}
	}
}

void AMyPlayer::AttackEnd()
{
	UE_LOG(LogTemp, Log, TEXT("AttackEnd"));
}

bool AMyPlayer::GetIsAttack()
{
	return m_bAttack;
}

void AMyPlayer::Dash()
{
	//현재 상태가 기본상태가 아니라면
	if (CurrentState != STATE_TYPE::STATE_DEFAULE)
		return;

	cDash->Execute(this);
}


void AMyPlayer::SetFringe(bool isOn)
{
	if (isOn) {
		PostProcessComponent->Settings.SceneFringeIntensity = 5.0f;
		//타이머 등록
		GetWorldTimerManager().SetTimer(m_ProcessingTimer, this, &AMyPlayer::DescreaseFringeIntensity, 0.1f, false);
	}
}

bool AMyPlayer::GetAttackTimeEnd()
{
	return m_bAttackTimeEnd;
}

void AMyPlayer::SetAttackTimeEnd()
{
	m_bAttackTimeEnd = false;
}

void AMyPlayer::DescreaseFringeIntensity()
{
	if (PostProcessComponent->Settings.SceneFringeIntensity <= 0.0f) {
		GetWorldTimerManager().SetTimer(m_ProcessingTimer, this, &AMyPlayer::DescreaseFringeIntensity, 0.5f, false);
		return;
	}
	else {
		GetWorldTimerManager().SetTimer(m_ProcessingTimer, this, &AMyPlayer::DescreaseFringeIntensity, 0.1f, false);
		PostProcessComponent->Settings.SceneFringeIntensity = PostProcessComponent->Settings.SceneFringeIntensity - 0.1f;
		float value = PostProcessComponent->Settings.SceneFringeIntensity;


		if (PostProcessComponent->Settings.SceneFringeIntensity <= 0.0f) {
			UE_LOG(LogTemp, Log, TEXT("DescreaseFringeIntensity"));
			GetWorldTimerManager().ClearTimer(m_ProcessingTimer);
		}
	}
}

//콤보가 리셋될 때 호출 됨.
void AMyPlayer::Itf_ResetCombo_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Itf_ResetCombo_Implementation"));
	//if(m_iCombo == 2)
	//	//Test : 슬로우 모션 제거
	//	GetWorld()->GetGameInstance<UMyGameInstance>()->EndSlowMotion();

	if (m_bCombo)
	{ //콤보 상태일 경우
		//콤보를 1 증가 시킨다.
		m_iCombo = (m_iCombo + 1) % 3;

		//다음 애니메이션을 재생시킨다.
		UAnimInstance * AnimInst = BladeMeshComponent->GetAnimInstance();
		if (PlayerAnimInst && AnimInst)
		{
			UE_LOG(LogTemp, Log, TEXT("Itf_ResetCombo_Implementation"));
			//PlayAnimMontage(AttackMontage, 1.f, FName(*FString::Printf(TEXT("attack%d"), m_iCombo)));

			//지금 진행중인 애니메이션이 끝나고 몽타주의 섹션을 건너뛰게 만들어 플레이.
			//PlayerAnimInst->Montage_SetNextSection(PlayerAnimInst->Montage_GetCurrentSection(), FName(*FString::Printf(TEXT("attack%d"), m_iCombo)), AttackMontage);
		}

		if (m_iCombo == 0) {
			//Test : 슬로우 모션 추가.
			/*GetWorld()->GetGameInstance<UMyGameInstance>()->StartSlowMotion();*/

			m_bAttackTimeEnd = true; //true 초기화한다.
			m_bAttack = false; //공격 상태를 false로 한다.
			m_iCombo = 0; //0으로 초기화한다.
		}

		//콤보 시스템 테스트
		//GetWorld()->GetGameInstance<UMyGameInstance>()->AddCombo();
	}
	else
	{ //콤보 상태가 아닐 경우
		m_bAttackTimeEnd = true; //true 초기화한다.
		m_bAttack = false; //공격 상태를 false로 한다.
		m_iCombo = 0; //0으로 초기화한다.

		//몽타주를 멈춘다.
		PlayerAnimInst->StopAllMontages(0.1f);
		BladeAnimInst->StopAllMontages(0.1f);
	}

	m_bCombo = false; //콤보 상태를 해제 시킨다.
	SetFringe(false);
}

void AMyPlayer::Itf_EndTakeDamage_Implementation()
{
	//피격 애니메이션이 종료 될 때 메시지가 오니까 false로 바꿔준다.
	m_bPlayTakeDamageAnimation = false;
	isAttackNotBlock = true;
}

//죽음 애니메이션이 끝날 때 호출
void AMyPlayer::Itf_DeathAnimEnd_Implementation()
{
	UiText->DeadCheck();
	//GetWorld()->GetTimerManager().SetTimer(ResurrectionTimerHandle, this, &AMyPlayer::Resurrection, ResurrectionTime, false);
}

//부활 애니메이션 끝날 때 호출
void AMyPlayer::Itf_ResurrectionAnimEnd_Implementation()
{
	//현재 상태를 기본 상태로 바꾼다.
	CurrentState = STATE_TYPE::STATE_DEFAULE;
	//무적시간 후에 무적 해제하기.
	GetWorld()->GetTimerManager().SetTimer(InvincibilityTimerHandle, this, &AMyPlayer::SetInvincibilityEnd, InvincibilityTime, false);
}

void AMyPlayer::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//기본 상태가 아니라면 아무 동작도 하지 않는다.
	if (CurrentState != STATE_TYPE::STATE_DEFAULE)
		return;

	if (!m_bNotDeath) //죽음 상태일 경우 아무동작도 하지 않는다.
		return;

	if (m_bInvincibility) //무적 상태일 경우 아무동작도 하지 않는다.
		return;

	if (m_bUltimate) //각성 상태일 경우 아무동작도 하지 않는다.
		return;

	//태그가 enemy인 컴포넌트에 공격을 받았을 때
	if (OtherComp->ComponentHasTag("enemy")) {
		ABaseMonsterClass * monster = Cast<ABaseMonsterClass>(OtherActor);
		//ABaseMonsterClass * monster = (ABaseMonsterClass *)OtherActor->GetClass();
		if (!monster) //클래스가 다르므로
			return;
		//enemy의 공격을 받고 있는 중이 아니라면
		UE_LOG(LogTemp, Log, TEXT("충돌체크 %s m_isAttackAnim :: %d"), *monster->GetName(), (*monster).GetIsAttack());
		if (!monster->GetIsAttack()) {
			return;
		}

		//현재 회피 상황이 아니라면 더 이상 진행하지 않는다.
		if (CurrentState == STATE_TYPE::STATE_AVOIDING)
			return;

		//카메라 흔들기 실행.
		GetWorld()->GetGameInstance<UMyGameInstance>()->PlayCameraShake();

		if (monster->mode != 100) {
			isAttackNotBlock = true;
		}
		else if(monster->mode == 100){
			isAttackNotBlock = false;
		}
		TakePlayerDamage(HitDamageCalculation(monster->GetATK()), true);
	}
}

int AMyPlayer::GetATK()
{
	int atk = ATK * (m_iCombo + 1);
	return atk + CriticalCalculation();
}

void AMyPlayer::OnCompHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Log, TEXT("OnCompHit"));
}

bool AMyPlayer::GetPlayTakeDamageAnimation()
{
	return m_bPlayTakeDamageAnimation;
}

bool AMyPlayer::GetIsDie()
{
	return !m_bNotDeath;
}

bool AMyPlayer::GetIsDash()
{
	if (cDash)
		return cDash->isDashing;
	else
		return false;
}

//피격 데미지 계산 함수
float AMyPlayer::HitDamageCalculation(int attack_)
{
	//피격 데미지 = 공격자 공격능력 * (1-피격자 데미지 감소율)
	float hitDamage = attack_ * (1 - (CharDef / (CharDEFconst + CharDef)));

	UE_LOG(LogTemp, Log, TEXT("hitDamage :: %f"), hitDamage);
	return hitDamage;
}

//부활하는 상태
void AMyPlayer::Resurrection()
{
	//현재 상태를 부활하는 상태로 바꾼다.
	CurrentState = STATE_TYPE::STATE_RESURRECTION;

	//부활할 때 죽음 화면 없앤다.
	SetDeadScreen(0);

	//카메라를 바꾼다.
	SendMessageCamera(SendMessageType::RESURRECTION);

	//무적 상태를 만든다.
	m_bInvincibility = true;

	//사망상태가 아닌다는 것을 알린다.
	m_bNotDeath = true;

	//HP를 회복 시킨다.
	SetHP(MaxHP);

	//MP를 회복 시킨다.
	SetMP(CharMaxMp);

	//부활 몽타주를 재생한다.
	float checkPlayMontage = PlayAnimMontage(ResurrectionMontage, 1.f, FName("Default"));
	if (ResurrectionBladeMontage != NULL)
	{
		BladeAnimInst->Montage_Play(ResurrectionBladeMontage);
	}

	//몽타주 재생이 안된다면...
	if (checkPlayMontage == 0.0f) {
		UE_LOG(LogTemp, Log, TEXT("몽타주 재생이 안된다."));
		//현재 상태를 기본 상태로 바꾼다.
		CurrentState = STATE_TYPE::STATE_DEFAULE;
		//무적시간 후에 무적 해제하기.
		GetWorld()->GetTimerManager().SetTimer(InvincibilityTimerHandle, this, &AMyPlayer::SetInvincibilityEnd, InvincibilityTime, false);
	}
}

void AMyPlayer::SetInvincibilityEnd()
{
	UE_LOG(LogTemp, Log, TEXT("무적 시간이 종료되었습니다."));
	//무적시간 끝내기
	m_bInvincibility = false;
}