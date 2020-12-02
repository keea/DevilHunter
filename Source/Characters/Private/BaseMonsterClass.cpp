// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonsterClass.h"
#include "Engine.h"
#include "MyPlayer.h"
#include "MyGameInstance.h"



// Sets default values
ABaseMonsterClass::ABaseMonsterClass()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_IDLE);

	firstPos = false;
	TimeSet = DelayTime;

	//Trigger Component에 부딪히면 태그를 읽어와서 상태 바꿈.
	TriggerCompoent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Compoent"));
	TriggerCompoent->SetupAttachment(RootComponent);
	TriggerCompoent->SetHiddenInGame(false);
	TriggerCompoent->SetGenerateOverlapEvents(true);

	m_OnSkill = true;
	SetIsAttack(false);
}

// Called when the game starts or when spawned
void ABaseMonsterClass::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseMonsterClass::Tick(float DeltaTime)//여기서 상태 조절을 해야한다.
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonsterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseMonsterClass::Chase()//쫒기
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	//pHP = player->GetHP();

	float dircheck;
	Playerpos = PlayerCharacter->GetActorLocation();


	dircheck = FVector::DotProduct(GetActorForwardVector(), DirPos);
	//몬스터의 앞 벡터와 방향을 내적해서 앞면 판단

	if (dircheck > 0 || findChar == true)
	{//시야 내에 캐릭터가 있거나 캐릭터를 한번 찾았을 때
		findChar = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;

		//출처: https://wergia.tistory.com/141 [베르의 프로그래밍 노트]
			/*캐릭터를 이동시키기 전에 이동 방향과 현재 캐릭터의 방향이 다르면 캐릭터를 이동 방향으로 초당 640도의 회전 속도로 회전시킨다음 이동시킨다*/

		real_Speed = Speed;

		DirPos = DirPos * DirPos.Normalize(0.1);
	}
	else
	{
		real_Speed = 0;
		//움직이지않음
	}
	AddMovementInput(DirPos, real_Speed);
}
bool ABaseMonsterClass::DirCheck(float limit)
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	FVector dir = player->GetActorLocation() - GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("dir %f"), dir.Size()));

	if (dir.Size() < limit&&dir.Size() > -limit)
		return true;
	return false;
}

void ABaseMonsterClass::MonsterTakeDamage(int atk_damage)
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	GetWorld()->GetGameInstance<UMyGameInstance>()->AddCombo();
	if (mode == 1)
	{
		//몬스터 Hp 감소 이벤트
		player->UiText->MonHp();
		GetWorld()->GetGameInstance<UMyGameInstance>()->MonsterHitNotice(1);
	}
	else if (mode == 0)
	{
		player->UiText->MonHp();
		GetWorld()->GetGameInstance<UMyGameInstance>()->MonsterHitNotice(0);
	}
	int damage = atk_damage * d_transmittance;
	if (mode != 100)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CombatMontage)
		{
			AnimInstance->Montage_Play(CombatMontage, 1.f);
			AnimInstance->Montage_JumpToSection(FName("Hit"), CombatMontage);
		}
	}
		//PlayAnimMontage(AnimMontages[2], 0.5f, FName("Default"));//hit 애니메이션 재생
	SetHP(GetHP() - damage);//진짜 피격데미지

	SetTakeDamage(damage);
}

void ABaseMonsterClass::PlayerTakeDamage(int atk_damage)
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	player->TakePlayerDamage(atk_damage, true);
}

void ABaseMonsterClass::Return()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	Monsterpos = GetActorLocation();

	DirPos = FirPos - Monsterpos;

	if (DirPos.Size() > 50.0f)
		real_Speed = Speed;
	else
	{
		real_Speed = 0.0f;
	}

	DirPos = DirPos * DirPos.Normalize(0.1);//처음 위치로 돌아감
	AddMovementInput(DirPos, real_Speed);
}

void ABaseMonsterClass::Idle()
{
}

void ABaseMonsterClass::Dead()
{
	if (TriggerCompoent != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("mon_dead"));
		TriggerCompoent->DestroyComponent();
		TriggerCompoent = nullptr;
	}
	if (!m_isDead)
	{
		if (mode == 100)
		{//보스 죽을 때 슬로우 모션 실행.
			GetWorld()->GetGameInstance<UMyGameInstance>()->StartSlowMotion();

			m_isDead = true;
			m_DeadAnim = true;
		}
		else
		{
			if (mode == 0 || mode == 1)
			{
				GetWorld()->GetGameInstance<UMyGameInstance>()->AddKillMonsterCount();
			}
		}
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CombatMontage)
		{
			UE_LOG(LogTemp, Log, TEXT("death_Anim_Play"));
			AnimInstance->Montage_Play(CombatMontage, 1.f);
			AnimInstance->Montage_JumpToSection(FName("Death"), CombatMontage);
		}
		SetEnemyMovementStatus(EEnemyMovementStatus::EMS_DEAD);
		m_isDead = true;
		m_DeadAnim = true;
	}
	findChar = false;
	SetIsAttack(false);
}

bool ABaseMonsterClass::GetIsAttack()
{
	return m_isAttackAnim;
}

void ABaseMonsterClass::SetIsAttack(bool attack)
{
	m_isAttackAnim = attack;
}

void ABaseMonsterClass::Itf_MonATK_Implementation()
{
	SetIsAttack(false);
}

void ABaseMonsterClass::Itf_MonATK_START_Implementation()
{
	SetIsAttack(true);
	m_isAttack = false;
}

void ABaseMonsterClass::Itf_Skill_Damage_Implementation(float damage)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("HIT"));
	SetHP(GetHP() - damage);
}

int ABaseMonsterClass::GetTakeDamage()
{

	return Takedamage;
}

void ABaseMonsterClass::SetTakeDamage(int damage)
{
	Takedamage = damage;
}

void ABaseMonsterClass::AttackStart()
{
	SetIsAttack(true);
}

void ABaseMonsterClass::AttackEnd()
{
	SetIsAttack(false);
}

void ABaseMonsterClass::DeathEnd()
{
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;
	Destroy();
}

void ABaseMonsterClass::SkillEnd()
{
	m_OnSkill = true;
}

void ABaseMonsterClass::SkillStart()
{
	m_OnSkill = false;
}