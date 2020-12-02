// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "SoundList.h"
#include "MyPlayer.h"
#include "Engine/World.h"
#include "Camera/CameraShake.h"
#include "GameFramework/WorldSettings.h"

UMyGameInstance::UMyGameInstance() 
{
}

void UMyGameInstance::StartSlowMotion() 
{
	if (!isSlowMotion) 
	{
		GetWorld()->GetWorldSettings()->SetTimeDilation(0.2f);
		isSlowMotion = true;

		FTimerHandle WaitHandle;
		float WaitTime = 0.5f; //�ð��� �����ϰ�
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			// ���ο� ��� ����.
			//EndSlowMotion();
			GetWorld()->GetGameInstance<UMyGameInstance>()->EndSlowMotion();

		}), WaitTime, false, WaitTime);
	}
}

void UMyGameInstance::EndSlowMotion() 
{
	if (isSlowMotion) {
		GetWorld()->GetWorldSettings()->SetTimeDilation(1.0f);
		isSlowMotion = false;
	}
}

void UMyGameInstance::InitCombos()
{
	//�޺�, �ִ� �޺��� 0���� �ʱ�ȭ
	combo = 0;
	maximumCombo = 0;
}

void UMyGameInstance::AddCombo()
{
	//Ÿ�̸� ����
	GetWorld()->GetTimerManager().ClearTimer(comboResetTimer);

	//�޺� ���� 1����.
	combo += 1;

	//�޺� ���� Ÿ�̸� ����.
	GetWorld()->GetTimerManager().SetTimer(comboResetTimer, this, &UMyGameInstance::ResetCombo, comboHoldingTime, false);

	//�޺��� �ִ� �޺����� Ŭ ���
	if (combo > maximumCombo)
		maximumCombo = combo; //�ִ��޺��� ���� �޺��� ������ ��ȯ.

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	player->UiText->CreateCombo();

	UE_LOG(LogTemp, Log, TEXT("combo :: %i"), combo);
	UE_LOG(LogTemp, Log, TEXT("maximumCombo :: %i"), maximumCombo);
}

int UMyGameInstance::GetCombo()
{
	return combo;
}

int UMyGameInstance::GetMaximumCombo()
{
	return maximumCombo;
}

void UMyGameInstance::ResetCombo()
{
	combo = 0;
}

void UMyGameInstance::KillMonsterCountInit()
{
	killMonsterCount = 0;
}

void UMyGameInstance::AddKillMonsterCount()
{
	killMonsterCount++;
	
	//�븮�ڰ� ��ϵǾ� ���� ��
	if (Fuc_DeleMonsterDie.IsBound() == true) 
	{
		Fuc_DeleMonsterDie.Broadcast();
	}
}

int UMyGameInstance::GetKillMonsterCount()
{
	return killMonsterCount;
}

void UMyGameInstance::PlayCameraShake()
{
	//ī�޶� ����.
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(MyShake, 1.0f);
}

void UMyGameInstance::UltimateSkillUnlock()
{
	//��ų ����� �����Ų��.
	if (Fuc_UltimateSkillUnlock.IsBound() == true)
		Fuc_UltimateSkillUnlock.Execute();

	//�� �� ��������Ʈ�� �����Ѵ�.(�ѹ��� ����Ǳ� ������)
	Fuc_UltimateSkillUnlock.Unbind();
}

void UMyGameInstance::MonsterHitNotice(int type)
{
	if (Fuc_HitMonster.IsBound() == true)
		Fuc_HitMonster.Execute(type);
}
