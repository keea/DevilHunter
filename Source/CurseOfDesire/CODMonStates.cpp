// Fill out your copyright notice in the Description page of Project Settings.


#include "CODMonStates.h"
#include "Engine.h"
#include "CurseOfDesire.h"

CODMonStates::CODMonStates()
{
}

CODMonStates::~CODMonStates()
{
}

IDLE * IDLE::Instance()
{
	static IDLE idle;
	return &idle;
}

void IDLE::Enter(ACODMon * mon)
{
	//움직이지 않는다.
	mon->SetIsMonSpeed(0);
}

void IDLE::Execute(ACODMon * mon)
{//실행해야 하는 내용
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	FVector dir = player->GetActorLocation() - mon->GetActorLocation();

	float dircheck;
	
	dircheck = FVector::DotProduct(GetActorForwardVector(), dir);
	//몬스터의 앞 벡터와 방향을 내적해서 앞면 판단

	if (dircheck > 0 || mon->GetIsFindChar() == true)
	{
		if (dir.Size() > 1500.0f)
		{//움직이지 않음
			//real_Speed = 0;
		}
		else if (dir.Size() > 300.0f)
		{//추적해야함
			//real_Speed = Speed;
		}
	}

	else
	{//체력 회복
		if (mon->GetHP() < mon->GetMaxHP())
		{
			int curhp = mon->GetHP() + 100;
			mon->SetHP(curhp);

			
		}
		
		if (mon->GetHP() > mon->GetMaxHP())
			{
				mon->SetHP(mon->GetMaxHP());
			}
	}
	
	
}

void IDLE::Exit(ACODMon * mon)
{
}
