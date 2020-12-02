// Fill out your copyright notice in the Description page of Project Settings.


#include "testMon.h"
#include "Engine.h"
#include "MyGameInstance.h"
#include "MyPlayer.h"

// Sets default values
AtestMon::AtestMon()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SetIsAttack(false);
	SetATK(200);
	SetMaxHP(600);
	SetHP(GetMaxHP());

	MeleeCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeCollisionBox"));
	MeleeCollisionBox->SetupAttachment(RootComponent);
	MeleeCollisionBox->SetCollisionProfileName("enemy");
	MeleeCollisionBox->SetHiddenInGame(false);
	DelayTime = 2.0f;
	P_dieTime = 0;
	p_dieDelay = 2.0f;
	m_isPDead = false;
	firstPos = true;
	m_isFaintTime = false;
	m_isFaintTime = 0;
	m_isFaintDelayTime = 0.5f;
	m_bomTimeCheck = false;
	TimeSet = 0;
	DeadTime = 7.0f;
	d_transmittance = 1;
	m_isAttackTime = 100;
	m_isDead = false;
}

// Called when the game starts or when spawned
void AtestMon::BeginPlay()
{
	Super::BeginPlay();
	TriggerCompoent->OnComponentBeginOverlap.AddDynamic(this, &AtestMon::Trigger);
	//SetIsAttack(true);


	const FAttachmentTransformRules AttackmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	MeleeCollisionBox->AttachToComponent(GetMesh(), AttackmentRules, "M_Bip-L-Hand");
}

// Called every frame
void AtestMon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (!m_isDead)
	{
		if (firstPos)//ó�� ��ġ ����
		{
			firstPos = false;
			FirPos = GetActorLocation();
		}

		if (GetHP() <= 0)//���� ���
		{
			/*if(mode == 2)
			m_isDead = true;*/
			Dead();
		}
		else
		{
			if (!m_isAttack)//���� �ð� ����
			{
				m_isAttackTime += DeltaTime;

				if (m_isAttackTime > m_isAttackTimer)
				{
					m_isAttackTime = 0;
					m_isAttack = true;
				}
			}

			if (mode == 2)//������
			{
				//�ð� ���
				TimeSet += DeltaTime;
				if (TimeSet > DelayTime)
				{
					m_bomTimeCheck = true;
					SetIsAttack(false);
					SetHP(0);
					Dead();
					ExplosionDemage();
				}
			}
			//�ǰݽ� ���� Ȯ���ϰ� �������
			if (m_isFaint)//������ ��
			{//0.5�ʰ� ����
				m_isFaintTime += DeltaTime;
				if (m_isFaintTime > m_isFaintDelayTime)
				{
					m_isFaintTime = 0;
					m_isFaint = false;
				}
			}
			else//�ƴ� ��
			{
				PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);//�÷��̾� Ư��
				if (player->GetHP() <= 0)
				{
					if (mode == 2)//������
					{
						SetHP(0);
						Dead();
					}
					m_isPDead = true;
				}
				if (m_isPDead)//�ΰ� ��ġ��
				{

					P_dieTime += DeltaTime;
					if (P_dieTime >= p_dieDelay)
					{
						P_dieTime = 0;
						m_isPDead = false;
					}
				}
			}
		}
	}
}

// Called to bind functionality to input
void AtestMon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AtestMon::Trigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	if (OtherComp->ComponentHasTag("skill")) {
			MonsterTakeDamage(player->GetATK());
			skillHit = true;
	}

	else if (OtherComp->ComponentHasTag("Weapon")) {
		if (player && player->GetIsAttack()) { //�÷��̾ null�� �ƴϰ� ���ݻ����� ���
			//ī�޶� ���� ����.
			
			m_isFaint = true;//����->����(����)
			MonsterTakeDamage(player->GetATK());
			
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Debug %f"), GetHP()));
			if (GetHP() <= 0.f)
			{ //hp�� 0���
				MeleeCollisionBox->DestroyComponent();				
			}
		}
	}
}

void AtestMon::ExplosionDemage()//�Ÿ� Ȯ�� �� ������
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	FVector dir = player->GetActorLocation() - GetActorLocation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("dir %f"), dir.Size()));

	if (DirCheck(300.0f))
	{
		player->TakePlayerDamage(250, true);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("explosssssion"));
	}
}

void AtestMon::Itf_MonHIT_End_Implementation()//Skill6
{
	m_isHit = false;
	SetIsAttack(false);
}