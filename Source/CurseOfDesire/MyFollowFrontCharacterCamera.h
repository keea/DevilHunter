// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FollowCamera.h"
#include "MyFollowFrontCharacterCamera.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFDESIRE_API AMyFollowFrontCharacterCamera : public AFollowCamera
{
	GENERATED_BODY()
	
public:
	AMyFollowFrontCharacterCamera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//ī�޶� ȸ���� �����ϰ� Ȯ�����ּ���.
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	//FVector IntervalVectorShow;
};
