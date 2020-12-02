// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMonsterClass.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CODMon.h"
#include "CODPatrolMon.generated.h"

UCLASS()
class CHARACTERS_API ACODPatrolMon : public ABaseMonsterClass
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACODPatrolMon();
	float Timer;
	FVector dirpos;
	FVector velocity;
	float radius;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Idle() override;

	float real_Speed;
	float Speed;
};
