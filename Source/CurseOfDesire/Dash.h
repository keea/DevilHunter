// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Dash.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CURSEOFDESIRE_API UDash : public UObject
{
	GENERATED_BODY()

public:
	UDash();

	UFUNCTION()
	void Execute(class AMyPlayer * player);

	UFUNCTION()
	void DescreaseMotionBlur(class AMyPlayer * player);

	//대시 중지
	UFUNCTION()
	void StopDashing(class AMyPlayer * player);

	//대시 쿨타임 초기화
	UFUNCTION()
	void ResetDash(class AMyPlayer * player);

	//대시 중인가
	UPROPERTY()
	bool isDashing;
private:
	//대시 중단 시간(x초 후)
	UPROPERTY()
	float DashStop;
	UPROPERTY()
	float motionBlurWeight;
	

protected:
	//대시 모션 블록 타이머
	UPROPERTY()
	FTimerHandle m_MotionBlurTimer;

	//대시 종료 타이머
	UPROPERTY()
	FTimerHandle m_UnUsedDashTimer;

	//대시 쿨타임 타이머
	UPROPERTY()
	FTimerHandle m_DashCoolTimer;

	//기본 fov값
	UPROPERTY()
	float DefaultFOV;

public:
	//대시 거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setting)
	float DashDistance;

	//대시 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setting)
	float DashCooldown;

	//대시 스피드(0으로 하면 안움직인다.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setting)
	float DashSpeed;

	//대시 가능한 상태인지 확인
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setting)
	bool CanDash;

	//FOV 설정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setting)
	float ZoomInFieldOfView;

};
