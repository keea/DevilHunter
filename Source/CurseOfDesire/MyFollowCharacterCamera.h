// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FollowCamera.h"
#include "MyFollowCharacterCamera.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API AMyFollowCharacterCamera : public AFollowCamera
{
	GENERATED_BODY()
public:
	AMyFollowCharacterCamera();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
