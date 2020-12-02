// Fill out your copyright notice in the Description page of Project Settings.


#include "RockfallTrap.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "MyPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"

// Sets default values
ARockfallTrap::ARockfallTrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARockfallTrap::BeginPlay()
{
	Super::BeginPlay();

	//콜리전 함수와 연결
	TrapCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARockfallTrap::OnOverlapBegin);
	TrapCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseTrap::OnOverlapEnd);
	
	//파티클 이벤트 종료시
	TrapEffectComponent->OnSystemFinished.AddDynamic(this, &ABaseTrap::OnTrapEffectFinished);
}

// Called every frame
void ARockfallTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARockfallTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (isOnTrap) {
		AMyPlayer * player = Cast<AMyPlayer>(OtherActor);
		//함정 발동 타이머 실행.
		FTimerDelegate ActivateTrapDelegate = FTimerDelegate::CreateUObject(this, &ABaseTrap::OnActivateTrap, player);
		GetWorld()->GetTimerManager().SetTimer(m_ActivateTrapTimer, ActivateTrapDelegate, DamageDelayTime, false);
	}
}


void ARockfallTrap::OnActivateTrap(AMyPlayer * player)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("함정 발동")); // 화면출력

	//범위 이펙트를 지운다.
	PlayerEnterEffectComponent->SetTemplate(NULL);

	//트랩 이펙트를 실행시킨다.
	TrapEffectComponent->SetTemplate(TrapEffect);

	if (isOnTrap) { //만약 트랩 위에 있다면
		player->TakePlayerDamage(Damage, true); //데미지 입히기.
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("함정에 데미지 입음")); // 화면출력
	}
}

