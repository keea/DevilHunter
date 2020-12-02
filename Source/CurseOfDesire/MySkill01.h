// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicSkill.h"
#include "MySkill01.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API AMySkill01 : public ABasicSkill
{
	GENERATED_BODY()
		AMySkill01();

	virtual void BeginPlay() override;
public:
	virtual void Execute();
};
