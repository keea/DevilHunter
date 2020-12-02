// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "testChar.generated.h"


UCLASS()
class CURSEOFDESIRE_API AtestChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AtestChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	/*UPROPERTY(VisibleAnywhere, Category = Collision)
		UCapsuleComponent* Capsule;*/

	UPROPERTY(VisibleAnywhere, Category = Visual)
		USkeletalMeshComponent* CMesh;

	void AttackCheck();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;
};
