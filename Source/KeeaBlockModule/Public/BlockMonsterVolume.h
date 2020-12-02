// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockMonsterVolume.generated.h"

class UBoxComponent;
class UTextRenderComponent;

UCLASS(Blueprintable)
class KEEABLOCKMODULE_API ABlockMonsterVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockMonsterVolume();

	//components
	UBoxComponent * BoxCollsion;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Construction Script
	virtual void OnConstruction(const FTransform& Transform);

	//Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")
		float VolumeWidth = 32.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")
		float VolumeHeight = 32.0f;

	//막기를 해제할 몬스터 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")
	int NextKillMonster = 0;

	//몬스터 죽인 횟수 달성 시 엑터 제거
	UFUNCTION()
	void CheckMonsterKill();
};
