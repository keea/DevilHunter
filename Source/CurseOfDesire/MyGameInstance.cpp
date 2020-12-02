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
		float WaitTime = 0.5f; //시간을 설정하고
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 슬로우 모션 종료.
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
	//콤보, 최대 콤보를 0으로 초기화
	combo = 0;
	maximumCombo = 0;
}

void UMyGameInstance::AddCombo()
{
	//타이머 종료
	GetWorld()->GetTimerManager().ClearTimer(comboResetTimer);

	//콤보 수를 1증가.
	combo += 1;

	//콤보 리셋 타이머 실행.
	GetWorld()->GetTimerManager().SetTimer(comboResetTimer, this, &UMyGameInstance::ResetCombo, comboHoldingTime, false);

	//콤보가 최대 콤보보다 클 경우
	if (combo > maximumCombo)
		maximumCombo = combo; //최대콤보의 값을 콤보의 값으로 변환.

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
	
	//대리자가 등록되어 있을 때
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
	//카메라를 흔든다.
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(MyShake, 1.0f);
}

void UMyGameInstance::UltimateSkillUnlock()
{
	//스킬 언락을 실행시킨다.
	if (Fuc_UltimateSkillUnlock.IsBound() == true)
		Fuc_UltimateSkillUnlock.Execute();

	//그 후 델리게이트를 해제한다.(한번만 실행되기 때문에)
	Fuc_UltimateSkillUnlock.Unbind();
}

void UMyGameInstance::MonsterHitNotice(int type)
{
	if (Fuc_HitMonster.IsBound() == true)
		Fuc_HitMonster.Execute(type);
}
