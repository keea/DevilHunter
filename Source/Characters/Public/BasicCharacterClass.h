// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "BasicCharacterClass.h"
#include "BasicCharacterClass.generated.h"

UCLASS()
class CHARACTERS_API ABasicCharacterClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicCharacterClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//기본 공격력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int ATK; 
	
	//최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float MaxHP; 

	//현재 체력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float HP; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* 스탯 값 반환 함수들*/
	UFUNCTION()
	virtual int GetATK();

	UFUNCTION()
	virtual float GetMaxHP() const;

	UFUNCTION()
	virtual float GetHP() const;

	/* 스탯 값 변경 함수들*/
	UFUNCTION()
	virtual void SetATK(int _atk);

	UFUNCTION()
	virtual void SetMaxHP(float _maxHp);

	UFUNCTION()
	virtual void SetHP(int _hp);

	//콘솔 HP 변경
	UFUNCTION(BlueprintCallable, Category = "ConsolCmd")
	virtual void CMDSetHP(int _hp);
	
	//콘솔 ATK 변경
	UFUNCTION(BlueprintCallable, Category = "ConsolCmd")
	virtual void CMDSetATK(int _atk);
};
