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

	//��� �����ϳ�
	UPROPERTY(EditAnyWhere, Category = "Spawning")
		TSubclassOf<class AFBSkill> WhatToSpawn;

	//WhereToSpawn�� ��ȯ
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointInVolume();

	//TimeHandle�� ����
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
	//������ ������ġ ����
	UPROPERTY(VisibleAnyWhere, Category = "Spawning", meta = (AllowPrivateAccess = true))
		class UBoxComponent* WhereToSpawn;

	void SpawnPickup();

	//���� ������ �����̰�
	float SpawnDelay;

};
