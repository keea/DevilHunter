// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillInfo.h"
#include "SkillSpawn.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API USkillSpawn : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void Execute(FSkillInfo info);
};
