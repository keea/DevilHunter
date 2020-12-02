// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

APlayerCamera::APlayerCamera() 
{
	StartingCamera = false;
	GetCameraComponent()->SetFieldOfView(90.0f);
	//���� ��Ⱦ�� ������� ����.
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
			PlayerController->SetViewTarget(this, TransitionParams); //ī�޶� ��ȯ
		}
	}
}
