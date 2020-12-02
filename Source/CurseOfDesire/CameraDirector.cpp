// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	DefaultCamera = (AActor *)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;
}

void ACameraDirector::Itf_PlayerDie_Implementation()
{
	const float SmoothBlendTime = 0.75f;
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(DieCamera, SmoothBlendTime); //카메라 전환
}

void ACameraDirector::Itf_PlayerResurrection_Implementation()
{
	const float SmoothBlendTime = 0.75f;
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(DefaultCamera, SmoothBlendTime); //카메라 전환
}

void ACameraDirector::Itf_Skill_Ultimate_Start_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, __FUNCTION__);
	const float SmoothBlendTime = 0.75f;
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(UltimateCamera, SmoothBlendTime); //카메라 전환
}

void ACameraDirector::Itf_Skill_Ultimate_End_Implementation()
{
	const float SmoothBlendTime = 0.75f;
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(DefaultCamera, SmoothBlendTime); //카메라 전환
}

