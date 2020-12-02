// Fill out your copyright notice in the Description page of Project Settings.


#include "MBSkill.h"
#include "Engine.h"
#include "MyPlayer.h"

// Sets default values
AMBSkill::AMBSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	explosion = false;
	Timer = 0;
	bomb = true;
}

void AMBSkill::SpawnAoe()
{
	FActorSpawnParameters SpawnParams;

	FVector MLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);

	c_aoe = GetWorld()->SpawnActor<AActor>(Aoe, GetActorLocation(), GetActorRotation(), SpawnParams);
}

// Called when the game starts or when spawned
void AMBSkill::BeginPlay()
{
	Super::BeginPlay();
	SpawnAoe();
}

// Called every frame
void AMBSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	Timer += DeltaTime;
	if (Timer > TimeSet)
	{
			count++;
		Timer = 0;

		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);

		if (player->GetHP() <= 0)
		{
			explosion = true;
			c_aoe->Destroy();
		}

		if (count == 3)
		{
			c_aoe->Destroy();
			explosion = true;
			Timer = 0;

			FVector dir = player->GetActorLocation() - GetActorLocation();
			if (dir.Size() < attackdis)
			{
				player->TakePlayerDamage(2100.0f, true);
			}
		}
		
		if (count == 5)
		{
		
		}
	}	
}

