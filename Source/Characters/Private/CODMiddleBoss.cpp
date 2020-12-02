// Fill out your copyright notice in the Description page of Project Settings.


#include "CODMiddleBoss.h"
#include "Engine.h"
#include "MyPlayer.h"
#include "Condition.h"
#include "testMon.h"
#include "MyGameInstance.h"
#include "SingletonObject.h"


ACODMiddleBoss::ACODMiddleBoss()
{
	DelayTime = 2.0f;

	SetHP(1000);
	SetATK(2100);
	SetMaxHP(GetHP());
	m_isDead = false;
	currentState = 0;
	PrevIndex = 1000000;
	PatternIndex = -1;
	skill1 = false;
	skill2 = false;
	skill3 = false;
	decide = true;
	skill3check = true;
	TimeSet = 0;
	P_dieTime = 0;
	p_dieDelay = 2.0f;
	m_isPDead = false;
	firstPos = true;
	m_isFaint = false;
	m_isFaintTime = 0;
	m_isFaintDelayTime = 0.5f;
	faintCount = 0;
	Isonpattern = false;
	DeadTime = 10.0f;
	d_transmittance = 0.6f;
	m_isPlayPattern = false;
	PatternTimer = 99.0f;
	m_isRecover = false;
	m_isSkillDestroy = false;
	m_OnSkill = true;

	if (GEngine != NULL)
		instance = Cast < USingletonObject >(GEngine->GameSingleton);
}

void ACODMiddleBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetEnemyMovementStatus() != EEnemyMovementStatus::EMS_DEAD)
	{
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
		if (firstPos)
		{
			firstPos = false;
			FirPos = GetActorLocation();
		}
		if (GetHP() <= 0)
		{
			if (!m_isDead)
				GetWorld()->GetGameInstance<UMyGameInstance>()->UltimateSkillUnlock();
			Dead();

		}
		else {

			if (player->GetHP() <= 0)
			{
				if (m_isPDead != true)
					m_isPDead = true;
			}
			if (m_isPDead)
			{
				P_dieTime += DeltaTime;
				if (P_dieTime >= p_dieDelay)
				{
					Reset();
				}
			}
			else if (m_isFaint)//스턴일 때. 보스 - 7초간 스턴(기절)
			{
				m_isFaintTime += DeltaTime;
				if (m_isFaintTime > m_isFaintDelayTime)
				{
					m_isFaintTime = 0;
					m_isFaint = false;
					faintCount++;
					UE_LOG(LogTemp, Log, TEXT("mbfaint"));
					PatternTimer = 99;
				}
			}
			else//아닐때
			{
				{
					if (DirCheck(1000))//처음
						Isonpattern = true;

					if (Isonpattern)
					{
						if (m_OnSkill)
						{
							PatternTimer += DeltaTime;
							if (PatternTimer >= PatternTime)
							{
								PatternIndex += 1;
								PatternTimer = 0;
								Pattern();
								m_isPlayPattern = true;
							}
						}
					}

					if (flower1 != nullptr)
					{
						if (flower1->Alive)//체력회복
						{
							F1Timer += DeltaTime;
							if (F1Timer > 1.0f)
							{
								HpRecover();
								F1Timer = 0;
							}
						}
						else
						{
							m_isRecover = false;
							m_isSkillDestroy = true;
							F1Timer = 1;
							flower1 = nullptr;
						}
					}

				}
				if (flower2 != nullptr)
				{
					//체력회복
					if (flower2->Alive)//체력회복
					{
						F2Timer += DeltaTime;
						if (F2Timer > 1.0f)
						{
							HpRecover();
							F2Timer = 0;
							UE_LOG(LogTemp, Log, TEXT("MB HP Recover"));
						}
					}
					else
					{
						m_isRecover = false;
						m_isSkillDestroy = true;
						F2Timer = 1;
						flower2 = nullptr;
					}
				}
			}

		}
	}
}

void ACODMiddleBoss::BeginPlay()
{
	Super::BeginPlay();
	TriggerCompoent->OnComponentBeginOverlap.AddDynamic(this, &ACODMiddleBoss::Trigger);
}

void ACODMiddleBoss::Trigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	if (OtherComp->ComponentHasTag("skill")) {
		MonsterTakeDamage(player->GetATK());
	}
	if (OtherComp->ComponentHasTag("Weapon")) {
		if (player && player->GetIsAttack()) { //플레이어가 null이 아니고 공격상태일 경우
			MonsterTakeDamage(player->GetATK());
			GetWorld()->GetGameInstance<UMyGameInstance>()->MonsterHitNotice(2);

			AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
			if (player)
			{
				FVector ImpactPoint = player->BladeMeshComponent->GetSocketLocation("P_BN_Blade_Start");

				if (instance)
				{
					//피격 이벤트 피 이펙트 랜덤값 가져오기
					int randValue = FMath::RandRange(0, 3);
					UParticleSystem *SelectedEffect = instance->GetEffect((EEFFECTS)((int)EEFFECTS::blood1 + randValue));

					// 피 이펙트 추가
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, ImpactPoint, SweepResult.ImpactNormal.Rotation());
				}
				else
				{
					if (GEngine != NULL)
						instance = Cast < USingletonObject >(GEngine->GameSingleton);

					if (instance)
					{
						//피격 이벤트 피 이펙트 랜덤값 가져오기
						int randValue = FMath::RandRange(0, 3);
						UParticleSystem *SelectedEffect = instance->GetEffect((EEFFECTS)((int)EEFFECTS::blood1 + randValue));

						// 피 이펙트 추가
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, ImpactPoint, SweepResult.ImpactNormal.Rotation());
					}
				}
			}
		}
	}
}


void ACODMiddleBoss::Reset()
{
	P_dieTime = 0;
	m_isPDead = false;

	SetATK(2100);
	SetMaxHP(GetHP());
	m_isDead = false;
	currentState = 0;
	PrevIndex = 1000000;
	PatternIndex = -1;
	skill1 = false;
	skill2 = false;
	skill3 = false;
	decide = true;
	skill3check = true;
	TimeSet = 0;
	P_dieTime = 0;
	p_dieDelay = 2.0f;
	m_isPDead = false;
	firstPos = true;
	m_isFaintTime = false;
	m_isFaintTime = 0;
	m_isFaintDelayTime = 0.5f;
	faintCount = 0;
	Isonpattern = false;
	DeadTime = 10.0f;
	d_transmittance = 0.6f;
}

void ACODMiddleBoss::SpawnObject()//20초에 한번 두마리. 자폭
{
	FActorSpawnParameters SpawnParams;
	FVector MLocation = GetActorLocation() + FVector(FMath::RandPointInCircle(RadiusRange).X, FMath::RandPointInCircle(RadiusRange).Y, 0);

	AActor* spawnActorRef = GetWorld()->SpawnActor<AActor>(SpawnToMonster, MLocation, GetActorRotation(), SpawnParams);

	MLocation = GetActorLocation() + FVector(FMath::RandPointInCircle(RadiusRange).X, FMath::RandPointInCircle(RadiusRange).Y, 0);

	spawnActorRef = GetWorld()->SpawnActor<AActor>(SpawnToMonster, MLocation, GetActorRotation(), SpawnParams);

	skill3check = false;
}

void ACODMiddleBoss::SpawnFlower()
{
	FActorSpawnParameters SpawnParams;

	AActor* spawnActorRef = GetWorld()->SpawnActor<AActor>(SpawnToFlower, GetActorLocation() + FVector(FMath::RandPointInCircle(RadiusRange).X, FMath::RandPointInCircle(RadiusRange).Y, 0), FRotator::ZeroRotator, SpawnParams);

	flower1 = Cast<AMBFlower>(spawnActorRef);


	/*spawnActorRef = GetWorld()->SpawnActor<AActor>(SpawnToFlower, GetActorLocation() + FVector(FMath::RandPointInCircle(RadiusRange).X, FMath::RandPointInCircle(RadiusRange).Y, 0), FRotator::ZeroRotator, SpawnParams);

	flower2 = Cast<AMBFlower>(spawnActorRef);*/
}

void ACODMiddleBoss::SpawnMBSkill2()
{
	FActorSpawnParameters SpawnParams;
	//플레이어 로케이션에서 
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	FVector pLoc = player->GetActorLocation();

	GetWorld()->SpawnActor<AActor>(SpawnToSkill2, FVector(pLoc.X, pLoc.Y, 60), FRotator::ZeroRotator, SpawnParams);
}

void ACODMiddleBoss::Pattern()
{
	PlayPattern();

	switch (currentState)
	{
	case 0://공격1
		skill1 = true;
		skill2 = false;
		skill3 = false;
		break;

	case 1://공격2		
		skill2 = true;
		skill1 = false;
		skill3 = false;
		break;

	case 2://공격3
		skill3 = true;
		skill1 = false;
		skill2 = false;
		break;

	case 3://빈사상태
		if (GetHP() < GetMaxHP() / 10 || faintCount <= 4)//10% 미만 혹은 4 이하
		{
			CheckFaint();
			skill1 = false;
			skill2 = false;
			skill3 = false;
		}
		else
		{
			skill1 = true;
			skill2 = false;
			skill3 = false;
			currentState = 0;
		}
		break;

	default://대기/사망
		skill1 = false;
		skill2 = false;
		skill3 = false;
		m_isFaint = false;
		break;
	}
}


void ACODMiddleBoss::PlayPattern()
{
	int rand = 0;

	switch (PatternIndex)
	{
	case 0:
		currentState = 0;
		break;

	case 1:
		//playParticle = true;
		currentState = 1;
		break;

	case 2:
		currentState = 2;
		break;

	case 3:
		currentState = 3;
		break;

	case 4:
		currentState = 4;
		PatternIndex = -1;
		break;

	default:
		break;
	}
}

void ACODMiddleBoss::CheckFaint()
{
	if (!m_isFaint)
	{
		m_isPlayPattern = false;
		m_isFaint = true;
		SetEnemyMovementStatus(EEnemyMovementStatus::EMS_FAINT);
	}
}

void ACODMiddleBoss::Itf_MBSkill1_End_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("MBSkill1"));
	UE_LOG(LogTemp, Log, TEXT("MB Skill 1"));
	SpawnFlower();
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	player->UiText->MBFlowerCheck();

	m_isPlayPattern = false;
}

void ACODMiddleBoss::Itf_MBSkill2_Start_Implementation()
{
	SpawnMBSkill2();
	m_isPlayPattern = false;
}

void ACODMiddleBoss::Itf_MBSkill2_End_Implementation()
{
	SetIsAttack(false);

}

void ACODMiddleBoss::Itf_MBSkill3_Start_Implementation()
{
	skill3 = false;
	skill3check = false;
	m_isPlayPattern = false;
}

void ACODMiddleBoss::Itf_MBSkill3_End_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("MBSkill3"));
	UE_LOG(LogTemp, Log, TEXT("MB Skill3"));
	SpawnObject();

}

void ACODMiddleBoss::HpRecover()
{//2%회복
	UE_LOG(LogTemp, Log, TEXT("MB HP Recover"));
	int recover = GetMaxHP() / 80;
	if (!m_isRecover)
		m_isRecover = true;
	recover += GetHP();
	if (recover >= GetMaxHP())
	{
		recover = GetMaxHP();
	}
	SetHP(recover);
}

void ACODMiddleBoss::Skill01()
{
	UE_LOG(LogTemp, Log, TEXT("MB Skill 1"));
	SpawnFlower();
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	player->UiText->MBFlowerCheck();

	m_isPlayPattern = false;
}

void ACODMiddleBoss::Skill02()
{
	FActorSpawnParameters SpawnParams;
	//플레이어 로케이션에서 
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

	FVector pLoc = player->GetActorLocation();

	GetWorld()->SpawnActor<AActor>(SpawnToSkill2, FVector(pLoc.X, pLoc.Y, 60), FRotator::ZeroRotator, SpawnParams);
	m_isPlayPattern = false;
}

void ACODMiddleBoss::Skill03()
{
	skill3 = false;
	skill3check = false;
	m_isPlayPattern = false;
}

void ACODMiddleBoss::Skill03End()
{
	UE_LOG(LogTemp, Log, TEXT("MB Skill3"));
	SpawnObject();
}


