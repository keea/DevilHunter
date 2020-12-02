// Fill out your copyright notice in the Description page of Project Settings.


#include "CODMonSpawner.h"
#include "CODMiddleBoss.h"
#include "Engine.h"
#include "CurseOfDesire.h"
#include "MyPlayer.h"
#include "FBSkill.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACODMonSpawner::ACODMonSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	//
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	//스폰 딜레이 범위 설정
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHight = 4.5f;
	SpawnLimit = 5;
}

// Called when the game starts or when spawned
void ACODMonSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHight);
	//GetWorldTimerManager().SetTimer(SpawnTimer, this, &ACODMonSpawner::SpawnPickup, SpawnDelay, false);

	SpawnPickup();
}

// Called every frame
void ACODMonSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ACODMonSpawner::GetRandomPointInVolume()
{
		FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
		FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

		return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ACODMonSpawner::SpawnPickup()
{
	//스폰가능여부 확인
	if (WhatToSpawn != NULL)
	{
		//월드 유효
		UWorld* const World = GetWorld();
		if (World)
		{
			//생성
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			for (int i = 0; i < SpawnLimit; i++)
			{			//랜덤한 위치 
				FVector SpawnLocation = GetRandomPointInVolume();

				AFBSkill* const SpawnedPickup = World->SpawnActor<AFBSkill>(WhatToSpawn, SpawnLocation, GetActorRotation(), SpawnParams);

				/*SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHight);
				GetWorldTimerManager().SetTimer(SpawnTimer, this, &ACODMonSpawner::SpawnPickup, SpawnDelay, false);*/
			}
		}
	}
}


