// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicSkill.h"
#include "MySkill02.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API AMySkill02 : public ABasicSkill
{
	GENERATED_BODY()

public:
	AMySkill02();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SettingMovement)
	class UProjectileMovementComponent * ProjectileMovementComponent;

	//È÷Æ® ÀÌÆåÆ®
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effect, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * HitEffect;

	UFUNCTION()
	void FireInDirection(const FVector& ShootDirection);

	virtual void Execute();
};
