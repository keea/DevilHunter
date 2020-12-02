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
		if (firstPos)//처음 위치 지정
		{
			firstPos = false;
			FirPos = GetActorLocation();
		}

		if (GetHP() <= 0)//몬스터 사망
		{
			/*if(mode == 2)
			m_isDead = true;*/
			Dead();
		}
		else
		{
			if (!m_isAttack)//공격 시간 조절
			{
				m_isAttackTime += DeltaTime;

				if (m_isAttackTime > m_isAttackTimer)
				{
					m_isAttackTime = 0;
					m_isAttack = true;
				}
			}

			if (mode == 2)//봄버맨
			{
				//시간 재기
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
			//피격시 스턴 확인하게 해줘야함
			if (m_isFaint)//스턴일 때
			{//0.5초간 멈춤
				m_isFaintTime += DeltaTime;
				if (m_isFaintTime > m_isFaintDelayTime)
				{
					m_isFaintTime = 0;
					m_isFaint = false;
				}
			}
			else//아닐 때
			{
				PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);//플레이어 특정
				if (player->GetHP() <= 0)
				{
					if (mode == 2)//봄버맨
					{
						SetHP(0);
						Dead();
					}
					m_isPDead = true;
				}
				if (m_isPDead)//두개 합치기
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
		if (player && player->GetIsAttack()) { //플레이어가 null이 아니고 공격상태일 경우
			//카메라 흔들기 실행.
			
			m_isFaint = true;//맞음->기절(스턴)
			MonsterTakeDamage(player->GetATK());
			
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Debug %f"), GetHP()));
			if (GetHP() <= 0.f)
			{ //hp가 0라면
				MeleeCollisionBox->DestroyComponent();				
			}
		}
	}
}

void AtestMon::ExplosionDemage()//거리 확인 후 데미지
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