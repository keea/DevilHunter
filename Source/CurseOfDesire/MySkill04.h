// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicSkill.h"
#include "MySkill04.generated.h"

/**
 *
 */
UCLASS()
class CURSEOFDESIRE_API AMySkill04 : public ABasicSkill
{
	GENERATED_BODY()
		AMySkill04();
	virtual void BeginPlay() override;
public:
	virtual void Execute();
};
