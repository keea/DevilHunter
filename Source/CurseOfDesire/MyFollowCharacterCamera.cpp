// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFollowCharacterCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AMyFollowCharacterCamera::AMyFollowCharacterCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyFollowCharacterCamera::BeginPlay()
{
	
	TargetActor = (AActor *)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Super::BeginPlay();
}

void AMyFollowCharacterCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
