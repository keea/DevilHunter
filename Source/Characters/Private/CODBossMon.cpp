// Fill out your copyright notice in the Description page of Project Settings.


#include "CODBossMon.h"
#include "Engine.h"
#include "MyPlayer.h"
#include "CurseOfDesire.h"
#include "FBSkill.h"
#include "MyGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SingletonObject.h"

// Sets default values
ACODBossMon::ACODBossMon()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_DEAD_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_death_Montage.b_death_Montage'"));
	if (FB_DEAD_Montage.Succeeded()) {
		AnimMontages.Add(FB_DEAD_Montage.Object);
	}//Die

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_HIT_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_idle_Montage.b_idle_Montage'"));
	if (FB_HIT_Montage.Succeeded()) {
		AnimMontages.Add(FB_HIT_Montage.Object);
	}//Hit

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_FAINT_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_dying_Montage.b_dying_Montage'"));
	if (FB_FAINT_Montage.Succeeded()) {
		AnimMontages.Add(FB_FAINT_Montage.Object);
	}//Faint


	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_ATK1_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_pttrn1_Montage.b_pttrn1_Montage'"));
	if (FB_ATK1_Montage.Succeeded()) {
		AnimMontages.Add(FB_ATK1_Montage.Object);
	}//ATK1

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_ATK2_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_pttrn2_Montage.b_pttrn2_Montage'"));
	if (FB_ATK2_Montage.Succeeded()) {
		AnimMontages.Add(FB_ATK2_Montage.Object);
	}//ATK2

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_ATK3_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_idle_Montage.b_idle_Montage'"));
	if (FB_ATK3_Montage.Succeeded()) {
		AnimMontages.Add(FB_ATK3_Montage.Object);
	}//ATK3

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_ATK4_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_pttrn4_Montage.b_pttrn4_Montage'"));
	if (FB_ATK4_Montage.Succeeded()) {
		AnimMontages.Add(FB_ATK4_Montage.Object);
	}//ATK4

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_ATK5_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_pttrn5_Montage.b_pttrn5_Montage'"));
	if (FB_ATK5_Montage.Succeeded()) {
		AnimMontages.Add(FB_ATK5_Montage.Object);
	}//ATK5

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FB_ATK6_Montage(TEXT("AnimMontage'/Game/DevilHunter/FinalBoss/0630/b_pttrn6_Montage.b_pttrn6_Montage'"));
	if (FB_ATK6_Montage.Succeeded()) {
		AnimMontages.Add(FB_ATK6_Montage.Object);
	}//ATK6

	MeleeCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeCollisionBox"));
	MeleeCollisionBox->SetupAttachment(RootComponent);
	MeleeCollisionBox->SetCollisionProfileName("enemy");
	MeleeCollisionBox->SetHiddenInGame(false);

	MeleeCollisionBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeCollisionBox1"));
	MeleeCollisionBox1->SetupAttachment(RootComponent);
	MeleeCollisionBox1->SetCollisionProfileName("enemy");
	MeleeCollisionBox1->SetHiddenInGame(false);

	FBTriggerCompoent = CreateDefaultSubobject<UBoxComponent>(TEXT("FBTriggerCompoent"));
	FBTriggerCompoent->SetupAttachment(RootComponent);
	FBTriggerCompoent->SetCollisionProfileName("enemy");
	FBTriggerCompoent->SetHiddenInGame(false);

	PatternTime = 15.0f;
	SetMaxHP(48000);
	SetHP(GetMaxHP());
	SetATK(400);
	isBerserker = false;
	currentState = 0;
	skill3time = 20.0f;//����ȭ�� 15�ʷ� ����
	skill4Count = 0;
	evasion = true;//ȸ�� ����
	skill1 = false;
	skill2 = false;
	skill3 = false;
	skill4 = false;
	skill5 = false;
	skill6 = false;
	PatternIndex = 0;
	skilldelay = 99;
	playParticle = false;
	m_isFaint = false;
	d_transmittance = 0.5f;
	checkPlay = false;
	DeadTime = 8.0f;
	DieDelayTime = 0;
	decide = false;
	firstPos = true;

	//�̱��� ������Ʈ ����
	if (GEngine != NULL)
		instance = Cast < USingletonObject >(GEngine->GameSingleton);
}

void ACODBossMon::Trigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	if (OtherComp->ComponentHasTag("skill")) {
		MonsterTakeDamage(player->GetATK());
	}

	if (OtherComp->ComponentHasTag("Weapon")) {
		evasion = false;
		GetWorld()->GetGameInstance<UMyGameInstance>()->MonsterHitNotice(3);
		if (player && player->GetIsAttack()) { //�÷��̾ null�� �ƴϰ� ���ݻ����� ���
			MonsterTakeDamage(player->GetATK());

			AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
			if (player)
			{
				FVector ImpactPoint = player->BladeMeshComponent->GetSocketLocation("P_BN_Blade_Start");

				//�ǰ� �̺�Ʈ �� ����Ʈ ������ ��������
				int randValue = FMath::RandRange(0, 3);
				if (instance)
				{
					//�ǰ� �̺�Ʈ �� ����Ʈ ������ ��������
					int randValue = FMath::RandRange(0, 3);
					UParticleSystem *SelectedEffect = instance->GetEffect((EEFFECTS)((int)EEFFECTS::blood1 + randValue));

					// �� ����Ʈ �߰�
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, ImpactPoint, SweepResult.ImpactNormal.Rotation());
				}
				else
				{
					if (GEngine != NULL)
						instance = Cast < USingletonObject >(GEngine->GameSingleton);

					if (instance)
					{
						//�ǰ� �̺�Ʈ �� ����Ʈ ������ ��������
						int randValue = FMath::RandRange(0, 3);
						UParticleSystem *SelectedEffect = instance->GetEffect((EEFFECTS)((int)EEFFECTS::blood1 + randValue));

						// �� ����Ʈ �߰�
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, ImpactPoint, SweepResult.ImpactNormal.Rotation());
					}
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ACODBossMon::BeginPlay()
{
	Super::BeginPlay();

	const FAttachmentTransformRules AttackmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	TriggerCompoent->AttachToComponent(GetMesh(), AttackmentRules, "B_Bip-Spine1");

	TriggerCompoent->OnComponentBeginOverlap.AddDynamic(this, &ACODBossMon::Trigger);

	MeleeCollisionBox->AttachToComponent(GetMesh(), AttackmentRules, "B_Bip-L-Hand");
	MeleeCollisionBox1->AttachToComponent(GetMesh(), AttackmentRules, "B_Bip-R-Hand");

	MeleeCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACODBossMon::Trigger);
	MeleeCollisionBox1->OnComponentBeginOverlap.AddDynamic(this, &ACODBossMon::Trigger);

	FBTriggerCompoent->OnComponentBeginOverlap.AddDynamic(this, &ACODBossMon::Trigger);
}

// Called every frame
void ACODBossMon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_isDead)
	{
		if (!isBerserker)
		{
			if (GetHP() <= GetMaxHP() / 7)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("berserker"));
				isBerserker = true;
				BerserkerMode();
			}
		}

		if (firstPos)
		{
			firstPos = false;
			FirPos = GetActorLocation();
		}

		if (GetHP() <= 0)
		{
			Dead();
		}
		else
		{
			if (!checkPlay)
			{
				if (DirCheck(PlayLimt))
					checkPlay = true;
			}
			else
			{
				PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
				if (player->UiText->FBTimeOut)
				{
					if (aoe != nullptr)
					{
						aoe->Destroy();
					}
					if (!decide)
					{
						skill1 = true;
						skill2 = false;
						skill3 = false;
						skill4 = false;
						skill5 = false;
						skill6 = false;
						m_isFaint = false;
						decide = true;
						m_isPlayPattern = false;
						P_dieTime = 0;
						PlayAnimMontage(AnimMontages[2], 1.0f, FName("Default"));
						p_dieDelay = 4;
					}
					P_dieTime += DeltaTime;
					if (P_dieTime >= p_dieDelay)
					{
						p_dieDelay = 999;
						P_dieTime = 0;
						PlayAnimMontage(AnimMontages[4], 1.0f, FName("Default"));
					}
				}

				if (m_isFaint)//������ ��. ���� - 7�ʰ� ����(����)
				{
					m_isFaintTime += DeltaTime;
					if (m_isFaintTime > m_isFaintDelayTime)
					{
						m_isFaintTime = 0;
						m_isFaint = false;
						faintCount++;
						UE_LOG(LogTemp, Log, TEXT("Bfaint"));
						skilldelay = 99;
					}
				}
				else//�ƴҶ�
				{
					if (player->GetHP() <= 0)//�÷��̾� ���
					{
						if (m_isPDead != true)
						{
							Reset();
							m_isPDead = true;
						}

						if (m_isPDead)
						{
							P_dieTime += DeltaTime;
							if (P_dieTime >= p_dieDelay)
							{
								P_dieTime = 0;
								m_isPDead = false;
							}
						}
					}
					else
					{
						if (m_OnSkill)
						{
							skilldelay += DeltaTime;
							if (skilldelay > PatternTime)
							{
								PatternIndex += 1;
								skilldelay = 0;
								Pattern();
								m_isPlayPattern = true;
							}
						}
					}
				}

			}
		}
	}
}
// Called to bind functionality to input
void ACODBossMon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACODBossMon::BerserkerMode()//����ȭ
{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BerserkerMode"));
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	//FB ����ȭ �̺�Ʈ
	player->UiText->FBBerserk();

	UE_LOG(LogTemp, Log, TEXT("BerserkerMode"));
	PatternTime = 3.0f;
	SetATK(600);
}

void ACODBossMon::DevilSpear()//�����
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	PlayerTakeDamage(6666666);
	SetIsAttack(true);
}

void ACODBossMon::PlaySkill2(float DeltaTime)
{
	skill2Timer += DeltaTime;

	if (skill2Timer > 2.0f)
	{
		skill2Timer = 0;
		//PlayAnimMontage(AnimMontages[5], 1.0f, FName("Default"));
	}
}

void ACODBossMon::PlaySkill3()
{
}

void ACODBossMon::PatternRotation()
{
	int random = 0;
	if (faintCount > 4)//4 �̻��̸� 
	{
		m_isFaint = false;
		PatternIndex++;
	}

	switch (PatternIndex)
	{
	case 0://�����̵�. 20�ʿ� �ѹ�
		currentState = 2;
		break;
	case 1:
		currentState = 3;
		break;
	case 2:case 4://ȸ������.. ������ ������ ���� ����
		if (evasion)
		{
			currentState = 4;
		}
		else
			currentState = 3;
		break;
	case 3:
		//����
		currentState = 1;
		break;
	case 5://ȸ������.. ������ ������ ���� ����
		currentState = 6;
		break;
	case 6://������
		currentState = 6;
		break;
	case 7:case 8:case 9:case 10:case 11:case 12:case 13:case 14:
		random = rand() % 4;
		if (random == 0)
		{
			currentState = 3;
		}
		else if (random == 1)
		{
			currentState = 4;
		}
		else if (random == 2)
		{
			currentState = 1;
		}
		else if (random == 3)
		{
			currentState = 5;
		}
		break;
	case 15://����ȭ Ȯ��
		if (!isBerserker)
		{
			if (GetHP() < (GetMaxHP() / 7))
			{
				isBerserker = true;
				BerserkerMode();
			}
		}
		else
		{
			if (GetHP() < GetMaxHP() / 90)
				currentState = 6;
		}
		break;
	}


	if (GetHP() <= 0)//���
	{
		currentState = 9999;
	}
	//PrevIndex = PatternIndex;
}

void ACODBossMon::Pattern()
{
	//PatternRotation();
	playPattern();

	switch (currentState)
	{
	case 0://����1
		skill1 = true;
		skill2 = false;
		skill3 = false;
		skill4 = false;
		skill5 = false;
		skill6 = false;
		break;

	case 1://����2
		skill1 = false;
		skill2 = true;
		skill3 = false;
		skill4 = false;
		skill5 = false;
		skill6 = false;
		break;

	case 2:
		skill1 = false;
		skill2 = false;
		skill3 = true;
		skill4 = false;
		skill5 = false;
		skill6 = false;
		skilldelay = 99;
		break;

	case 3:
		skill1 = false;
		skill2 = false;
		skill3 = false;
		skill4 = true;
		skill5 = false;
		skill6 = false;
		evasion = true;
		break;

	case 4:
		skill1 = false;
		skill2 = false;
		skill3 = false;
		skill4 = false;
		skill5 = true;
		skill6 = false;
		break;

	case 5:
		skill1 = false;
		skill2 = false;
		skill3 = false;
		skill4 = false;
		skill5 = false;
		skill6 = true;
		break;

	case 6://���
		if (GetHP() < GetMaxHP() / 10 || faintCount <= 4)//10% �̸� Ȥ�� 4 ����
		{
			skill1 = false;
			skill2 = false;
			skill3 = false;
			skill4 = false;
			skill5 = false;
			skill6 = false;
			m_isFaint = true;
		}
		else
		{
			skill1 = false;
			skill2 = true;
			skill3 = false;
			skill4 = false;
			skill5 = false;
			skill6 = false;

			currentState = 0;
		}

		break;

	default://���
		skill1 = false;
		skill2 = false;
		skill3 = false;
		skill4 = false;
		skill5 = false;
		skill6 = false;
		break;
	}
}

void ACODBossMon::Itf_FBSkill1_Start_Implementation()//�����
{
	if (skill1)
	{
		SetATK(999999);//
		SetIsAttack(true);
		DevilSpear();
	}
}

void ACODBossMon::Itf_FBSkill2_Start_Implementation()//������.
{
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(PlaySkill02, GetActorLocation() + FVector(0, 0, -170), FRotator::ZeroRotator, SpawnParams);

	//GetActorForwardVector()
}

void ACODBossMon::Itf_FBSkill3_Start_Implementation()//���� ��ġ �̵�
{
	skill3 = false;
	SetIsAttack(false);
}
void ACODBossMon::Itf_FBSkill4_Start_Implementation()//����
{//���� �� ���� ����
	FActorSpawnParameters SpawnParams;

	SetIsAttack(true);

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	FVector dir = player->GetActorLocation() - GetActorLocation();

	if (skill4Count == 0)
	{
		SetATK(600);
		skill4Count = 1;
		aoe = GetWorld()->SpawnActor<AActor>(RoundAOE1, GetActorLocation() + FVector(0, 0, -180), FRotator::ZeroRotator, SpawnParams);
		aoe->SetActorScale3D(FVector(15, 15, 1));
		skilldelay = 99;
	}
	else
	{
		aoe = GetWorld()->SpawnActor<AActor>(RoundAOE2, GetActorLocation() + FVector(0, 0, -180), FRotator::ZeroRotator, SpawnParams);
		SetATK(800);
		skill4Count = 0;
		aoe->SetActorScale3D(FVector(15, 15, 1));
	}

}

void ACODBossMon::Itf_FBSkill4_End_Implementation()//����
{
	UE_LOG(LogTemp, Log, TEXT("skill4"));
	SetIsAttack(false);
	//if (skill4Count == 1)
	skill4 = false;

	aoe->Destroy();

	if (DirCheck(LimitDir))
	{
		PlayerTakeDamage(GetATK());
	}
}

void ACODBossMon::Itf_FBSkill5_Start_Implementation()//Skill5 
{
	FActorSpawnParameters SpawnParams;
	playParticle = true;
	SetIsAttack(true);
	(GetWorld()->SpawnActor<AActor>(PlaySkill5, GetActorLocation() + FVector(0, 0, -40), GetActorRotation(), SpawnParams));

	(GetWorld()->SpawnActor<AActor>(PlaySkill5, GetActorLocation() + FVector(0, 0, -40), GetActorRotation() + FRotator(0, 90, 0), SpawnParams));
}

void ACODBossMon::Itf_FBSkill5_End_Implementation()//Skill5
{
	skill5 = false;
	playParticle = false;
	SetIsAttack(false);
}

void ACODBossMon::Itf_FBSkill6_Start_Implementation()//Skill6
{
	FActorSpawnParameters SpawnParams;
	playParticle = true;
	SetIsAttack(true);

	for (int i = 0; i < 8; i++)
	{
		GetWorld()->SpawnActor<AActor>(PlaySkill6, GetActorLocation() + FVector(0, 0, 0), GetActorRotation() + FRotator(0, i * 45, 0), SpawnParams);
	}
}

void ACODBossMon::Itf_FBSkill6_End_Implementation()//Skill6
{
	skill6 = false;
	playParticle = false;
	SetIsAttack(false);
}

void ACODBossMon::playPattern()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Pattern"));
	switch (PatternIndex)
	{
	case 0:
		currentState = 1;//��ų2
		break;
	case 1:
		currentState = 2;//��ų3
		break;
	case 2:
		currentState = 3;//��ų4
		break;

	case 3:
		currentState = 4;//��ų5
		skilldelay -= 5;
		break;
	case 4:
		currentState = 5;//��ų6
		break;

	case 5:
		currentState = 6;//���
		PatternIndex = -1;
		break;
	}

	if (GetHP() <= 0)//���
	{
		currentState = 9999;
	}
}

void ACODBossMon::Reset()
{
	PatternTime = 15.0f;
	SetMaxHP(48000);
	SetHP(GetMaxHP());
	SetATK(400);
	isBerserker = false;
	currentState = 0;
	skill3time = 20.0f;//����ȭ�� 15�ʷ� ����
	skill4Count = 0;
	evasion = true;//ȸ�� ����
	skill1 = false;
	skill2 = false;
	skill3 = false;
	skill4 = false;
	skill5 = false;
	skill6 = true;
	PatternIndex = 0;
	skilldelay = 0;
	playParticle = false;
	m_isFaint = false;
	d_transmittance = 0.5f;
}

void ACODBossMon::Skill01()
{
	m_isDead = true;
	playParticle = true;
	SetATK(999999);
	SetIsAttack(true);

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	PlayerTakeDamage(6666666);
	SetIsAttack(true);
}

void ACODBossMon::Skill02()//������ġ
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;

	GetCharacterMovement()->MaxWalkSpeed = 50000.f;

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(PlaySkill02, GetActorLocation() + FVector(0, 0, -170), FRotator::ZeroRotator, SpawnParams);
}

void ACODBossMon::Skill03()//�����̵�
{

}

void ACODBossMon::Skill04_Fir()//����. ù��°
{
	FActorSpawnParameters SpawnParams;

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	FVector dir = player->GetActorLocation() - GetActorLocation();

	SetATK(600);
	skill4Count = 1;
	aoe = GetWorld()->SpawnActor<AActor>(RoundAOE1, GetActorLocation() + FVector(0, 0, -180), FRotator::ZeroRotator, SpawnParams);
	aoe->SetActorScale3D(FVector(15, 15, 1));
	skilldelay = 99;
}

void ACODBossMon::Skill04_Sec()//����. �ι�°
{
	FActorSpawnParameters SpawnParams;

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	FVector dir = player->GetActorLocation() - GetActorLocation();


	aoe = GetWorld()->SpawnActor<AActor>(RoundAOE2, GetActorLocation() + FVector(0, 0, -180), FRotator::ZeroRotator, SpawnParams);
	SetATK(800);
	skill4Count = 0;
	aoe->SetActorScale3D(FVector(15, 15, 1));
}

void ACODBossMon::Skill04_End()//����.
{
	FBSkill4_End();
	UE_LOG(LogTemp, Log, TEXT("skill4"));
	SetIsAttack(false);
	//if (skill4Count == 1)
	skill4 = false;
	aoe->Destroy();

	if (DirCheck(LimitDir))
	{
		PlayerTakeDamage(GetATK());
	}
}

void ACODBossMon::Skill05()//������
{
	FActorSpawnParameters SpawnParams;
	playParticle = true;
	SetIsAttack(true);
	
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	(GetWorld()->SpawnActor<AActor>(PlaySkill5,FVector(5860.0f, 0.f, 0.0f), GetActorRotation(), SpawnParams));
	//end
}

void ACODBossMon::Skill05End()//������
{
	
	
	skill5 = false;
	playParticle = false;
	SetIsAttack(false);
}

void ACODBossMon::Skill06()//�߻�
{
	FActorSpawnParameters SpawnParams;
	playParticle = true;
	SetIsAttack(true);

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	(GetWorld()->SpawnActor<AActor>(PlaySkill6, FVector(5860.0f, 0.f, 0.0f), GetActorRotation(), SpawnParams));
}

void ACODBossMon::Skill06End()//�߻�
{
	

	skill6 = false;
	playParticle = false;
	SetIsAttack(false);
}
