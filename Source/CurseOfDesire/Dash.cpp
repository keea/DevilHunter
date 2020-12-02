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
	//초기에는 0으로 설정한다.
	motionBlurWeight = 0.f;

	//대시 상태가 가능하도록 초기화.
	CanDash = true;
	//대시 거리는 일단 3000으로
	DashDistance = 3000.0f;
	//쿨타임 설정
	DashCooldown = 8.f;
	//대시 속도
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

		//카메라 회전 값 가져오기
		FRotator rotation = playerController->GetControlRotation();
		//카메라 방향으로 회전
		player->SetActorRotation(rotation);

		player->LaunchCharacter(FVector(player->GetActorForwardVector().X, player->GetActorForwardVector().Y, 0).GetSafeNormal()*speed, true, true);
		CanDash = false;

		//타이머를 실행한다.
		DashStop = 1.f;
		FTimerDelegate UnUsedDashDelegate = FTimerDelegate::CreateUObject(this, &UDash::StopDashing, player);
		GetWorld()->GetTimerManager().SetTimer(m_UnUsedDashTimer, UnUsedDashDelegate, DashStop / (DashSpeed + (DashSpeed - 1)), false);

		//가중치를 1로 설정한다.
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
