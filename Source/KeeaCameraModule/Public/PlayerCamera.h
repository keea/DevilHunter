// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "PlayerCamera.generated.h"

/**
 * 
 */
UCLASS()
class KEEACAMERAMODULE_API APlayerCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	APlayerCamera();

	//Begin Play
	virtual void BeginPlay() override;

	//properties
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Camera Settings")
	bool StartingCamera;
};
