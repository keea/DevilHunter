// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

APlayerCamera::APlayerCamera() 
{
	StartingCamera = false;
	GetCameraComponent()->SetFieldOfView(90.0f);
	//고정 종횡비를 사용하지 않음.
	GetCameraComponent()->bConstrainAspectRatio = false;
}

void APlayerCamera::BeginPlay()
{
	if (StartingCamera) 
	{
		APlayerController * PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController) 
		{
			FViewTargetTransitionParams TransitionParams;
			PlayerController->SetViewTarget(this, TransitionParams); //카메라 전환
		}
	}
}
