// Fill out your copyright notice in the Description page of Project Settings.


#include "StartBackground.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStartBackground::AStartBackground()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStartBackground::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0); //���� ����� ù ��° �÷��̾� ����

	OurPlayerController->SetViewTarget(MyActor);
}

// Called every frame
void AStartBackground::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

