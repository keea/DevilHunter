// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManager.h"
#include "MyPlayer.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BasicSkill.h"
#include "MySkillUltimate.h"
#include "EngineUtils.h"
#include "SkillSpawn.h"
#include "UIText.h"
#include "Animation/AnimInstance.h"
#include "MySkill01.h"
#include "MySkill04.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "MyGameInstance.h"
#include "Engine/Engine.h"

// Sets default values
ASkillManager::ASkillManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASkillManager::BeginPlay()
{
	Super::BeginPlay();
	isFail = false;

	//언락 델리게이트 등록한다.
	if (GetWorld()->GetGameInstance<UMyGameInstance>() != NULL)
	{
		GetWorld()->GetGameInstance<UMyGameInstance>()->Fuc_UltimateSkillUnlock.BindUFunction(this, FName("UltimateSkillUnlock"));
	}
}

// Called every frame
void ASkillManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASkillManager::UseSkill(AMyPlayer * player, int type)
{
	FSkillInfo skill = SkillInfo[type];
	p_Player = player;

	//스킬이 락인 경우
	if (!skill.isUnRock)
		return false;

	//MP가 적은 경우
	if (player->GetMp() < skill.MP) {
		UE_LOG(LogTemp, Log, TEXT("MP부족"));
		return false;
	}

	//스킬을 사용할 수 없는 경우.(쿨타임)
	if (!skill.isCanSkill)
	{
		UE_LOG(LogTemp, Log, TEXT("쿨타임"));
		return false;
	}

	//몽타주 실행
	float check = player->PlayAnimMontage(skill.UseSkillMontages, skill.AnimSpeed, FName("Default"));
	float bladeCheck = 0.0f;
	if (skill.UseSkillBladeMontages != NULL)
		bladeCheck = player->BladeAnimInst->Montage_Play(skill.UseSkillBladeMontages);

	//몽타주 실행하지 못한다면...
	if (check <= 0.0f || bladeCheck <= 0.0f) {
		isFail = true;
		//애니메이션 노티파이 실행.
		if (player->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true) {
			IItf_AnimationNotify::Execute_Itf_Skill_Anim(player, type);
		}
	}

	//MP를 감소시킨다.
	player->SetMP(player->GetMp() - skill.MP);

	//카메라 변환을 알림.
	if (type == 4 || type == 3)
		player->SendMessageCamera(SendMessageType::ULTIMATE_START);

	SkillInfo[type].isCanSkill = false;

	//무적상태로 바꾼다.
	player->CurrentState = STATE_TYPE::STATE_SKILLING;
	player->m_bInvincibility = true;
	player->UiText->SkillChecker(type, skill.m_UnUsedSkillTimer, skill.Cooldown);

	return true;
}

void ASkillManager::Skill01()
{
	UWorld * World = GetWorld();
	if (World)
	{
		FSkillInfo skill = SkillInfo[0];
		if (skill.SkillClass)
		{
			APlayerController * playerController = UGameplayStatics::GetPlayerController(this, 0);
			FVector MuzzleLocation = playerController->GetPawn()->GetActorLocation();
			//MuzzleLocation.Y -= 250.0f;
			//MuzzleLocation.Z = 0.0f;

			//forward 백터를 구한 후
			FVector ForwardVector = playerController->GetPawn()->GetActorForwardVector();
			ForwardVector.Normalize(); //정규화함.
			ForwardVector *= 100.0f;

			FRotator MuzzleRotation = playerController->GetPawn()->GetActorRotation();

			UE_LOG(LogTemp, Log, TEXT("Skill0"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = Instigator;
			ABasicSkill* Skill = World->SpawnActor<ABasicSkill>(skill.SkillClass, (MuzzleLocation + ForwardVector), MuzzleRotation, SpawnParams);
			Skill->Execute();
			UE_LOG(LogTemp, Log, TEXT("Skill->Execute()"));
			FTimerDelegate SkillResetDelegate = FTimerDelegate::CreateUObject(this, &ASkillManager::ResetSkill, 0);
			GetWorldTimerManager().SetTimer(skill.m_UnUsedSkillTimer, SkillResetDelegate, skill.Cooldown, false);
			UE_LOG(LogTemp, Log, TEXT("Skill SetTimer"));
		}
	}
}

void ASkillManager::Skill02()
{
	FSkillInfo skill = SkillInfo[1];

	if (skill.SkillClass) {
		FVector CameraLocation;
		FRotator CameraRotation;

		APlayerController * playerController = UGameplayStatics::GetPlayerController(this, 0);
		playerController->GetPawn()->GetActorEyesViewPoint(CameraLocation, CameraRotation);
		FVector MuzzleLocation = playerController->GetPawn()->GetActorLocation();
		FRotator MuzzleRotation = playerController->GetPawn()->GetActorRotation();
		MuzzleRotation.Pitch += 10.0f;

		UWorld * World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = Instigator;
			ABasicSkill* Skill = World->SpawnActor<ABasicSkill>(skill.SkillClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Skill) {
				FVector LaunchDirection = playerController->GetPawn()->GetActorForwardVector();
				Skill->Execute();
				FTimerDelegate SkillResetDelegate = FTimerDelegate::CreateUObject(this, &ASkillManager::ResetSkill, 1);
				GetWorldTimerManager().SetTimer(skill.m_UnUsedSkillTimer, SkillResetDelegate, skill.Cooldown, false);
			}
		}
	}
}

void ASkillManager::Skill03()
{
	FSkillInfo skill = SkillInfo[2];

	UWorld * World = GetWorld();
	if (World)
	{
		if (skill.SkillClass) {
			APlayerController * playerController = UGameplayStatics::GetPlayerController(this, 0);
			FVector MuzzleLocation = playerController->GetPawn()->GetActorLocation();
			MuzzleLocation.Y -= 50.0f;
			MuzzleLocation.Z = 0.0f;
			FRotator MuzzleRotation = playerController->GetPawn()->GetActorRotation();
			UE_LOG(LogTemp, Log, TEXT("Skill03"));

			UWorld * World = GetWorld();
			if (World) {
				UE_LOG(LogTemp, Log, TEXT("Skill03"));
				FActorSpawnParameters SpawnParams;
				SpawnParams.Instigator = Instigator;
				ABasicSkill* Skill = World->SpawnActor<ABasicSkill>(skill.SkillClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				Skill->Execute();
				FTimerDelegate SkillResetDelegate = FTimerDelegate::CreateUObject(this, &ASkillManager::ResetSkill, 2);
				GetWorldTimerManager().SetTimer(skill.m_UnUsedSkillTimer, SkillResetDelegate, skill.Cooldown, false);
			}
		}
	}
}

void ASkillManager::Skill04()
{
	UWorld * World = GetWorld();
	if (World) {
		FSkillInfo skill = SkillInfo[3];
		if (skill.SkillClass) {
			APlayerController * playerController = UGameplayStatics::GetPlayerController(this, 0);
			FVector MuzzleLocation = playerController->GetPawn()->GetActorLocation();
			FRotator MuzzleRotation = playerController->GetPawn()->GetActorRotation();

			UWorld * World = GetWorld();
			if (World) {
				UE_LOG(LogTemp, Log, TEXT("Skill04"));
				FActorSpawnParameters SpawnParams;
				SpawnParams.Instigator = Instigator;
				ABasicSkill* Skill = World->SpawnActor<ABasicSkill>(skill.SkillClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				Skill->Execute();
				UE_LOG(LogTemp, Log, TEXT("Skill->Execute()"));
				FTimerDelegate SkillResetDelegate = FTimerDelegate::CreateUObject(this, &ASkillManager::ResetSkill, 3);
				GetWorldTimerManager().SetTimer(skill.m_UnUsedSkillTimer, SkillResetDelegate, skill.Cooldown, false);
				UE_LOG(LogTemp, Log, TEXT("Skill SetTimer"));
			}
		}
	}
}

void ASkillManager::SkillUltimate()
{

	UWorld * World = GetWorld();
	if (World) {
		FSkillInfo skill = SkillInfo[4];
		if (skill.SkillClass) {
			APlayerController * playerController = UGameplayStatics::GetPlayerController(this, 0);
			FVector MuzzleLocation = playerController->GetPawn()->GetActorLocation();
			MuzzleLocation.Y -= 50.0f;
			MuzzleLocation.Z = 0.0f;
			FRotator MuzzleRotation = playerController->GetPawn()->GetActorRotation();

			UWorld * World = GetWorld();
			if (World) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Instigator = Instigator;
				ABasicSkill* Skill = World->SpawnActor<ABasicSkill>(skill.SkillClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				Skill->Execute();
			}
		}
	}
}

void ASkillManager::Itf_Skill_Anim_Implementation(int skillType)
{
	//이것을 다른 액터에서 처리가 가능하도록 만들어야 한다.
	switch (skillType)
	{
	case 0:
	{
		Skill01();
	}
	break;
	case 1:
	{
		Skill02();
	}
	break;
	case 2:
	{
		Skill03();
	}
	break;
	case 3:
	{
		Skill04();
	}
	break;
	case 4:
	{
		SkillUltimate();
	}
	break;

	default:
		break;
	}

	//실패 시
	if (isFail)
	{
		if (p_Player->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true)
		{
			if (skillType == 3 || skillType == 4)
			{
				FTimerDelegate SkillResetDelegate = FTimerDelegate::CreateUObject(this, &ASkillManager::FailSkill, skillType);
				FTimerHandle m_UnUsedSkillTimer;
				GetWorldTimerManager().SetTimer(m_UnUsedSkillTimer, SkillResetDelegate, 3.0f, false);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("스킬 초기화"));
				FTimerDelegate SkillResetDelegate = FTimerDelegate::CreateUObject(this, &ASkillManager::FailSkill, skillType);
				FTimerHandle m_UnUsedSkillTimer;
				GetWorldTimerManager().SetTimer(m_UnUsedSkillTimer, SkillResetDelegate, 0.5f, false);
			}
		}
	}
}

void ASkillManager::Itf_Skill_End_Implementation(int skillType)
{
	UE_LOG(LogTemp, Log, TEXT("ASkillManager::Itf_Skill_End_Implementation(int skillType)"));
	if (skillType == 4) {
		for (TActorIterator<AMySkillUltimate> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			AMySkillUltimate * Skill = Cast<AMySkillUltimate>(*ActorItr);
			if (Skill) {
				Skill->Delete();
			}
		}
		FTimerDelegate SkillResetDelegate = FTimerDelegate::CreateUObject(this, &ASkillManager::ResetSkill, skillType);
		GetWorldTimerManager().SetTimer(SkillInfo[skillType].m_UnUsedSkillTimer, SkillResetDelegate, SkillInfo[skillType].Cooldown, false);
	}

	if (skillType == 0)
	{
		for (TActorIterator<AMySkill01> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			AMySkill01 * Skill1 = Cast<AMySkill01>(*ActorItr);

			if (Skill1 && skillType == 0)
			{
				Skill1->Delete();
			}
		}
	}

	if (skillType == 3) 
	{
		for (TActorIterator<AMySkill04> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			AMySkill04 * Skill4 = Cast<AMySkill04>(*ActorItr);
			UE_LOG(LogTemp, Log, TEXT("Skill4 skillType == 3"));
			if (Skill4 && skillType == 3)
			{
				UE_LOG(LogTemp, Log, TEXT("Skill4 Delete"));
				Skill4->Delete();
			}
		}
	}
}

void ASkillManager::FailSkill(int skillType)
{
	IItf_AnimationNotify::Execute_Itf_Skill_End(p_Player, skillType);
	IItf_AnimationNotify::Execute_Itf_Skill_Anim_End(p_Player, skillType);
}

void ASkillManager::UltimateSkillUnlock()
{
	UE_LOG(LogTemp, Log, TEXT("UltimateSkillUnlock"));
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
	player->UiText->UnlockAwake();
	SkillInfo[4].isUnRock = true;
}

void ASkillManager::ResetSkill(int type)
{
	UE_LOG(LogTemp, Log, TEXT("ResetSkill"));
	SkillInfo[type].isCanSkill = true;
}

