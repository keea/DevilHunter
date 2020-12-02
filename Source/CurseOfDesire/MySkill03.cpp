// Fill out your copyright notice in the Description page of Project Settings.


#include "MySkill03.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "MyPlayer.h"
#include "SingletonObject.h"
#include "MyGameInstance.h"
#include "TimerManager.h"
#include "Components/PointLightComponent.h"
#include "Engine/Engine.h"

AMySkill03::AMySkill03() {
	
}

void AMySkill03::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AMyPlayer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		player = Cast<AMyPlayer>(*ActorItr);
		if (player)
		{
			break;
		}
	}
}

// ��ų �ߵ�
void AMySkill03::Execute()
{
	UE_LOG(LogTemp, Log, TEXT("MySkill03 Execute()"));

	USingletonObject *  instance = NULL;
	if (GEngine != NULL)
		instance = Cast < USingletonObject >(GEngine->GameSingleton);


	//���� ����Ʈ�� �����Ѵ�.
	player->BuffSkillComponent->SetTemplate(BuffEffect);

	//����Ʈ ����
	if (instance != NULL) 
	{
		UGameplayStatics::SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_skill3_3_2),
			player->GetMesh(), "P_Bip-R-Hand",
			FVector(0, 0, 0), FRotator(0, 0, 0),
			EAttachLocation::KeepRelativeOffset, true);

		//Į�� ������ �Ѵ�.
		player->BladePointLightComponent->SetIntensity(7000.0f);
	}

	//������ ���۵Ǿ��ٴ� ���� �÷��̾�� �˸���.
	if (player->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true) 
	{
		IItf_AnimationNotify::Execute_Itf_Skill_Buff_Start(player);
	}

	GetWorldTimerManager().SetTimer(m_SkillEndTimer,this,&AMySkill03::EndSkill, SkillDuration, false);
}

// ��ų ���ӽð� ���� ��.
void AMySkill03::EndSkill()
{
	UE_LOG(LogTemp, Log, TEXT("MySkill03 EndSkill"));

	//Į�� ������ �ϴ� ���� �����Ѵ�.
	player->BladePointLightComponent->SetIntensity(0.0f);
	//������ �����ٴ� ���� �÷��̾�� �˸���.
	if (player->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true) {
		IItf_AnimationNotify::Execute_Itf_Skill_Buff_End(player);
	}
	Delete();
}
