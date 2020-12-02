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
	//�������� �ʴ´�.
	mon->SetIsMonSpeed(0);
}

void IDLE::Execute(ACODMon * mon)
{//�����ؾ� �ϴ� ����
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	FVector dir = player->GetActorLocation() - mon->GetActorLocation();

	float dircheck;
	
	dircheck = FVector::DotProduct(GetActorForwardVector(), dir);
	//������ �� ���Ϳ� ������ �����ؼ� �ո� �Ǵ�

	if (dircheck > 0 || mon->GetIsFindChar() == true)
	{
		if (dir.Size() > 1500.0f)
		{//�������� ����
			//real_Speed = 0;
		}
		else if (dir.Size() > 300.0f)
		{//�����ؾ���
			//real_Speed = Speed;
		}
	}

	else
	{//ü�� ȸ��
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
