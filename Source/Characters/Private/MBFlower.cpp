// Fill out your copyright notice in the Description page of Project Settings.


#include "MBFlower.h"
#include "Engine.h"
#include "MyPlayer.h"
#include "CurseOfDesire.h"
// Sets default values
AMBFlower::AMBFlower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetMaxHP(5);
	SetHP(GetMaxHP());
	Alive = true;
	atkcount = 0;
}

// Called when the game starts or when spawned
void AMBFlower::BeginPlay()
{
	Super::BeginPlay();
	TriggerCompoent->OnComponentBeginOverlap.AddDynamic(this, &AMBFlower::Trigger);
}

// Called every frame
void AMBFlower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSet += DeltaTime;
	if (TimeSet > DeleteTime)
	{
		Alive = false;
				
			SetHP( 0);
		
	}

	if (GetHP() <= 0)
	{
		Alive = false;
		m_isDead = true;
		Destroy();
	}
}

void AMBFlower::Trigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Weapon")) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("FlowerHIT"));
		AMyPlayer* player = Cast<AMyPlayer>(OtherActor);

		if (player && player->GetIsAttack()) { //플레이어가 null이 아니고 공격상태일 경우
			UE_LOG(LogTemp, Log, TEXT("mon_dead"));
			atkcount+=1;
			SetHP(GetHP() - 1);
			Alive = false;			
		}
	}
}
