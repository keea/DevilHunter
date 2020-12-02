// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFollowFrontCharacterCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

AMyFollowFrontCharacterCamera::AMyFollowFrontCharacterCamera() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyFollowFrontCharacterCamera::BeginPlay()
{
	TargetActor = (AActor *)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Super::BeginPlay();
}

void AMyFollowFrontCharacterCamera::Tick(float DeltaTime)
{
	FTransform targetTransform = TargetActor->GetActorTransform();
	//방향 벡터 구하기
	FVector forwardVector =  TargetActor->GetActorForwardVector();
	FVector changeTransform = targetTransform.GetLocation() + (forwardVector * 500.0f);
	FTransform newTransform = DefaultCamera->GetTransform();
	newTransform.SetLocation(changeTransform);
	DefaultCamera->SetActorTransform(newTransform);

	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(newTransform.GetLocation(), targetTransform.GetLocation());
	DefaultCamera->SetActorRotation(Rotator);
}
