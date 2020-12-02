// Fill out your copyright notice in the Description page of Project Settings.


#include "FBSkill.h"
#include "MyPlayer.h"
#include "Engine.h"
#include "CurseOfDesire.h"
#include "Condition.h"

// Sets default values
AFBSkill::AFBSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FBSkillTriggerCompoent = CreateDefaultSubobject<UBoxComponent>(TEXT("FBTrigger Compoent"));
	FBSkillTriggerCompoent->SetWorldScale3D(FVector(1, 1, 1));
	FBSkillTriggerCompoent->SetWorldLocation(GetActorLocation());
	FBSkillTriggerCompoent->SetupAttachment(RootComponent);
	FBSkillTriggerCompoent->SetHiddenInGame(true);
	FBSkillTriggerCompoent->SetGenerateOverlapEvents(true);
	seet = true;
	skilltype = 5;
	a_scale = 1;
	scaleSpeed = 0;
	Timer = 9999;
	TimeDelay = 3;
	m_idOverlap = false;
	Skillplay = true;
}

// Called when the game starts or when spawned
void AFBSkill::BeginPlay()
{
	Super::BeginPlay();
	FBSkillTriggerCompoent->OnComponentBeginOverlap.AddDynamic(this, &AFBSkill::Trigger);

	if (RoundAOE1)
	{
		FActorSpawnParameters SpawnParams;
		aoe = GetWorld()->SpawnActor<AActor>(RoundAOE1, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
		aoe->SetActorScale3D(FVector(8, 8, 1));
	}
}

// Called every frame
void AFBSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (seet == true)
	{
		seet = false;
		//Direction = GetActorForwardVector() - UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();//FRotationMatrix(GetActorForwardVector());

	}

	Timer += DeltaTime;

	if (Timer > TimeDelay)
	{
		Timer = 0;
		FActorSpawnParameters SpawnParams;

		if (Skillplay)//스킬 플레이 가능한가?
		{
			Skillplay = false;

			if (aoe)
				aoe->Destroy();

			PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			player = Cast<AMyPlayer>(PlayerCharacter);

			if (player)
			{
				if (m_idOverlap)
				{
					if (skilltype == 6)
					{
						player->TakePlayerDamage(500, true);
					}

					if (skilltype == 5)
					{
						player->SetCondition<float>(STAT_MANABURN, 30.0f);
					}
				}
			}

		}
	}
}

void AFBSkill::Trigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp) {

		player = Cast<AMyPlayer>(OtherActor);

		if (player)
		{
			m_idOverlap = true;
			if (skilltype == 5)//1500
			{
				
				UE_LOG(LogTemp, Log, TEXT("FB Skill5"));
			}

			if (skilltype == 6)//1500
			{
				UE_LOG(LogTemp, Log, TEXT("FB Skill6"));
				//player->TakePlayerDamage(player->HitDamageCalculation(300), true);
			}

			if (skilltype == 2)
			{
				PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				player = Cast<AMyPlayer>(PlayerCharacter);

				
			}
			//Destroy();
		}
	}
}

void AFBSkill::SetSkillType(int type)
{
	skilltype = type;
}