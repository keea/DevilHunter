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

	//Trigger Component�� �ε����� �±׸� �о�ͼ� ���� �ٲ�.
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
void ABaseMonsterClass::Tick(float DeltaTime)//���⼭ ���� ������ �ؾ��Ѵ�.
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonsterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseMonsterClass::Chase()//�i��
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	//pHP = player->GetHP();

	float dircheck;
	Playerpos = PlayerCharacter->GetActorLocation();


	dircheck = FVector::DotProduct(GetActorForwardVector(), DirPos);
	//������ �� ���Ϳ� ������ �����ؼ� �ո� �Ǵ�

	if (dircheck > 0 || findChar == true)
	{//�þ� ���� ĳ���Ͱ� �ְų� ĳ���͸� �ѹ� ã���� ��
		findChar = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;

		//��ó: https://wergia.tistory.com/141 [������ ���α׷��� ��Ʈ]
			/*ĳ���͸� �̵���Ű�� ���� �̵� ����� ���� ĳ������ ������ �ٸ��� ĳ���͸� �̵� �������� �ʴ� 640���� ȸ�� �ӵ��� ȸ����Ų���� �̵���Ų��*/

		real_Speed = Speed;

		DirPos = DirPos * DirPos.Normalize(0.1);
	}
	else
	{
		real_Speed = 0;
		//������������
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
		//���� Hp ���� �̺�Ʈ
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
		//PlayAnimMontage(AnimMontages[2], 0.5f, FName("Default"));//hit �ִϸ��̼� ���
	SetHP(GetHP() - damage);//��¥ �ǰݵ�����

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

	DirPos = DirPos * DirPos.Normalize(0.1);//ó�� ��ġ�� ���ư�
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
		{//���� ���� �� ���ο� ��� ����.
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