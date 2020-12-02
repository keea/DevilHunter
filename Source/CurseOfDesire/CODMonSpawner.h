// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CODMonSpawner.generated.h"

UCLASS()
class CURSEOFDESIRE_API ACODMonSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACODMonSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//어떤걸 스폰하나
	UPROPERTY(EditAnyWhere, Category = "Spawning")
		TSubclassOf<class AFBSkill> WhatToSpawn;

	//WhereToSpawn값 반환
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointInVolume();

	//TimeHandle형 변수
	FTimerHandle SpawnTimer;

	//Minimum Spawn Delay
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeLow;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
		int SpawnLimit;

	//Maximum Spawn Delay
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeHight;

private:
	//아이템 스폰위치 지정
	UPROPERTY(VisibleAnyWhere, Category = "Spawning", meta = (AllowPrivateAccess = true))
		class UBoxComponent* WhereToSpawn;

	void SpawnPickup();

	//현재 아이템 딜레이값
	float SpawnDelay;

};
