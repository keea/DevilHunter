// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTrap.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "MyPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Engine/Engine.h"

// Sets default values
ABaseTrap::ABaseTrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//나이아가라 이펙트는 기본으로 사용하지 않음으로 한다.
	isUseNiagaraEffect = false; //사용시는 프로퍼티에서 true로

	//박스콜리젼 컴포넌트 생성.
	TrapCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeCollisionBox"));
	TrapCollisionBox->SetupAttachment(RootComponent);
	TrapCollisionBox->SetHiddenInGame(false); //일단 보이도록 한다.

	//트랩 효과 파티클 컴포넌트 생성.
	TrapEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrapParticleSystem"));
	//범위 지정 이펙트 파티클 컴포넌트 생성.
	PlayerEnterEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlayerEnterEffectComponent"));

	//나이아가라 컴포넌트 생성
	TrapNiagaraEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrapNiagaraEffectComponent"));


	//트랩 이펙트 기본 설정.
	static ConstructorHelpers::FObjectFinder<UParticleSystem> trapEffect(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_lightning2.P_ky_lightning2'"));
	if (trapEffect.Succeeded()) {
		TrapEffect = trapEffect.Object;
	}
}

// Called when the game starts or when spawned
void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();

	isOnTrap = false;

	//콜리전 함수와 연결
	TrapCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrap::OnOverlapBegin);
	TrapCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseTrap::OnOverlapEnd);

	//트랩 컴포넌트 설정.
	TrapEffectComponent->SetupAttachment(RootComponent);
	TrapEffectComponent->bAutoActivate = true;
	TrapEffectComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	//범위 지정 이펙트 컴포넌트 설정
	PlayerEnterEffectComponent->SetupAttachment(RootComponent);
	PlayerEnterEffectComponent->bAutoActivate = true;
	PlayerEnterEffectComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	TrapNiagaraEffectComponent->bAutoActivate = false;
	TrapNiagaraEffectComponent->SetupAttachment(RootComponent);
	TrapNiagaraEffectComponent->SetAsset(TrapNiagaraEffect);
	TrapNiagaraEffectComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	
}

// Called every frame
void ABaseTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Player")) { //플레이어가 밟는다면...
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("함정 밟음.")); // 화면출력
		if (!isUseNiagaraEffect)
			PlayerEnterEffectComponent->SetTemplate(PlayerEnterEffect); //범위 표시
		else{
			TrapNiagaraEffectComponent->SetActive(true);
		}
			
		isOnTrap = true;
	}
}

void ABaseTrap::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentHasTag("Player")) { //플레이어가 벗어난다면
		isOnTrap = false;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("함정 피함")); // 화면출력
	}
}

void ABaseTrap::OnTrapEffectFinished(UParticleSystemComponent * System)
{
	//이펙트 표시가 끝나면 삭제한다.
	Destroy();
}

void ABaseTrap::OnTrapNiagaraEffectFinished(UNiagaraComponent * PSystem)
{
	//이펙트 표시가 끝나면 삭제한다.
	Destroy();
}

