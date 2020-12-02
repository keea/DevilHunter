// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillSpawn.h"
#include "MySkillSpawn03.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API UMySkillSpawn03 : public USkillSpawn
{
	GENERATED_BODY()
public:
	virtual void Execute(FSkillInfo info);
};
