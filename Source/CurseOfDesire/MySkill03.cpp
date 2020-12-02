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

// 스킬 발동
void AMySkill03::Execute()
{
	UE_LOG(LogTemp, Log, TEXT("MySkill03 Execute()"));

	USingletonObject *  instance = NULL;
	if (GEngine != NULL)
		instance = Cast < USingletonObject >(GEngine->GameSingleton);


	//버프 이펙트를 지정한다.
	player->BuffSkillComponent->SetTemplate(BuffEffect);

	//이펙트 실행
	if (instance != NULL) 
	{
		UGameplayStatics::SpawnEmitterAttached(instance->GetEffect(EEFFECTS::player_skill3_3_2),
			player->GetMesh(), "P_Bip-R-Hand",
			FVector(0, 0, 0), FRotator(0, 0, 0),
			EAttachLocation::KeepRelativeOffset, true);

		//칼을 빛나게 한다.
		player->BladePointLightComponent->SetIntensity(7000.0f);
	}

	//버프가 시작되었다는 것을 플레이어에게 알린다.
	if (player->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true) 
	{
		IItf_AnimationNotify::Execute_Itf_Skill_Buff_Start(player);
	}

	GetWorldTimerManager().SetTimer(m_SkillEndTimer,this,&AMySkill03::EndSkill, SkillDuration, false);
}

// 스킬 지속시간 끝날 시.
void AMySkill03::EndSkill()
{
	UE_LOG(LogTemp, Log, TEXT("MySkill03 EndSkill"));

	//칼을 빛나게 하는 것을 종료한다.
	player->BladePointLightComponent->SetIntensity(0.0f);
	//버프가 끝났다는 것을 플레이어에게 알린다.
	if (player->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true) {
		IItf_AnimationNotify::Execute_Itf_Skill_Buff_End(player);
	}
	Delete();
}
