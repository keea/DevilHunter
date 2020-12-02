// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "MBSkill.generated.h"

UCLASS()
class CHARACTERS_API AMBSkill : public AActor
{
	GENERATED_BODY()
		
public:
	// Sets default values for this actor's properties
	AMBSkill();

	float Timer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
		float TimeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
		float attackdis;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
		bool explosion;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AActor> Aoe;

	AActor* c_aoe;
	ACharacter* PlayerCharacter;
	void SpawnAoe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
bool bomb;
int count;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
