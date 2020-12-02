// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockMonsterVolume.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "MyGameInstance.h"

// Sets default values
ABlockMonsterVolume::ABlockMonsterVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Box Collsion
	BoxCollsion = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollsion;
	BoxCollsion->SetCollisionProfileName(TEXT("PlayerBlock"));
	BoxCollsion->SetBoxExtent(FVector(1.5f, 32.0f, 32.0f));
}

// Called when the game starts or when spawned
void ABlockMonsterVolume::BeginPlay()
{
	Super::BeginPlay();

	//��������Ʈ ����ϱ�
	if (GetWorld()->GetGameInstance<UMyGameInstance>() != NULL) {
		GetWorld()->GetGameInstance<UMyGameInstance>()->Fuc_DeleMonsterDie.AddUFunction(this, FName("CheckMonsterKill"));
	}
	
}

// Called every frame
void ABlockMonsterVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlockMonsterVolume::OnConstruction(const FTransform & Transform)
{
	BoxCollsion->SetBoxExtent(FVector(1.5f, VolumeWidth, VolumeHeight));
}

void ABlockMonsterVolume::CheckMonsterKill()
{
	//���� ���� Ƚ���� ũ��
	if (GetWorld()->GetGameInstance<UMyGameInstance>()->GetKillMonsterCount() >= NextKillMonster) 
	{
		//�ش� ���͸� �����Ѵ�.
		Destroy();
	}
}

