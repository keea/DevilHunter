// Fill out your copyright notice in the Description page of Project Settings.


#include "Dash.h"
#include "MyPlayer.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

UDash::UDash() {
	isDashing = false;

	DashStop = 1.f;
	//�ʱ⿡�� 0���� �����Ѵ�.
	motionBlurWeight = 0.f;

	//��� ���°� �����ϵ��� �ʱ�ȭ.
	CanDash = true;
	//��� �Ÿ��� �ϴ� 3000����
	DashDistance = 3000.0f;
	//��Ÿ�� ����
	DashCooldown = 8.f;
	//��� �ӵ�
	DashSpeed = 1.f;
	//FOV
	ZoomInFieldOfView = 60.0f;

	DefaultFOV = 90.0f;
}

void UDash::Execute(AMyPlayer * player)
{
	if (CanDash) {
		player->UiText->DashCheck();
		player->GetOurCamera()->FieldOfView = ZoomInFieldOfView;
		isDashing = true;

		APlayerController * playerController = player->GetController()->CastToPlayerController();

		float speed = DashDistance * DashSpeed;
		player->GetCharacterMovement()->BrakingFrictionFactor = 0.f;

		//ī�޶� ȸ�� �� ��������
		FRotator rotation = playerController->GetControlRotation();
		//ī�޶� �������� ȸ��
		player->SetActorRotation(rotation);

		player->LaunchCharacter(FVector(player->GetActorForwardVector().X, player->GetActorForwardVector().Y, 0).GetSafeNormal()*speed, true, true);
		CanDash = false;

		//Ÿ�̸Ӹ� �����Ѵ�.
		DashStop = 1.f;
		FTimerDelegate UnUsedDashDelegate = FTimerDelegate::CreateUObject(this, &UDash::StopDashing, player);
		GetWorld()->GetTimerManager().SetTimer(m_UnUsedDashTimer, UnUsedDashDelegate, DashStop / (DashSpeed + (DashSpeed - 1)), false);

		//����ġ�� 1�� �����Ѵ�.
		motionBlurWeight = 1;
		player->SetMotionBlerWeight(motionBlurWeight);

		FTimerDelegate DescreaseMotionBlurDelegate = FTimerDelegate::CreateUObject(this, &UDash::DescreaseMotionBlur, player);
		GetWorld()->GetTimerManager().SetTimer(m_MotionBlurTimer, DescreaseMotionBlurDelegate, 0.1f, false);
		player->ShowDashEffect();
		player->SetDashFresnel(motionBlurWeight);
	}
	else {
		isDashing = false;
	}
}

void UDash::DescreaseMotionBlur(AMyPlayer * player)
{
	float discrease = (DashStop / (DashSpeed + (DashSpeed - 1))) / 10.0f;
	motionBlurWeight = motionBlurWeight - discrease;

	if (motionBlurWeight > 0.0f) {
		player->SetMotionBlerWeight(motionBlurWeight);
		FTimerDelegate DescreaseMotionBlurDelegate = FTimerDelegate::CreateUObject(this, &UDash::DescreaseMotionBlur, player);
		GetWorld()->GetTimerManager().SetTimer(m_MotionBlurTimer, DescreaseMotionBlurDelegate, discrease, false);
	}
	else {
		player->SetMotionBlerWeight(0.f);
		GetWorld()->GetTimerManager().ClearTimer(m_MotionBlurTimer);
		return;
	}
}

void UDash::StopDashing(class AMyPlayer * player)
{
	isDashing = false;
	player->DashEnd();
	player->GetCharacterMovement()->StopMovementImmediately();
	player->GetCharacterMovement()->BrakingFrictionFactor = 2.f;

	player->GetOurCamera()->FieldOfView = DefaultFOV;

	FTimerDelegate DashEndDelegate = FTimerDelegate::CreateUObject(this, &UDash::ResetDash, player);
	GetWorld()->GetTimerManager().SetTimer(m_DashCoolTimer, DashEndDelegate, DashCooldown, false);
}

void UDash::ResetDash(class AMyPlayer * player)
{
	CanDash = true;
}
