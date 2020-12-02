// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicSkill.h"
#include "MySkillUltimate.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API AMySkillUltimate : public ABasicSkill
{
	GENERATED_BODY()
	// Sets default values for this actor's properties
	AMySkillUltimate();

	virtual void BeginPlay() override;
public:
	virtual void Execute();

//±Ã±Ø±â ¹«Àû ½Ã°£
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	float UltimateTime = 5.0f;
};
