// Fill out your copyright notice in the Description page of Project Settings.


#include "CODPatrolMon.h"
#include "Engine.h"
#include "CurseOfDesire.h"
#include "MyPlayer.h"

// Sets default values
ACODPatrolMon::ACODPatrolMon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> IronMaskSK(TEXT("/Game/Mesh/IronMaskSK.IronMaskSK"));

	//if (IronMaskSK.Succeeded())
	//{
	//	GetMesh()->SetSkeletalMesh(IronMaskSK.Object);
	//}
	Speed = 30;
	real_Speed = Speed;
	Timer = 2.0f;
}

// Called when the game starts or when spawned
void ACODPatrolMon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACODPatrolMon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	Timer += DeltaTime;
	if (Timer > 0.5f)
	{
		Timer = 0;
		Idle();
	}
	real_Speed = Speed;
	real_Speed *= DeltaTime;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, __FUNCTION__);
	AddMovementInput(dirpos, real_Speed);
}

// Called to bind functionality to input
void ACODPatrolMon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACODPatrolMon::Idle()
{
	int randommove = FMath::RandRange(0, 4);
	FVector dir;
	dir = FVector(0, 0, 0);

	switch (randommove)
	{
	case 0:
		dir = FVector(1, 1, 0);
		break;

	case 1:
		dir = FVector(-1, -1, 0);
		break;

	/*case 2:
		dir = FVector(-1, 0, 0);
		break;

	case 3:
		dir = FVector(0, -1, 0);
		break;*/

	default:
		break;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %i"), randommove));
	dir = GetActorForwardVector() + dir;

	dir.Normalize(0.1);
	dirpos = dir;
}

