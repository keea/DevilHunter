// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "LockSpringArmComponent.generated.h"

UENUM(BlueprintType)
enum class EDirection : uint8
{
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right"),
};

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) //블루프린트가 컴포넌트 클래스를 스폰.
class CURSEOFDESIRE_API ULockSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()
	
public:
	// 타켓으로 부터 최대 거리.
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
		float MaxTargetLockDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
		bool bUseSoftLock;

	// 디버그 보이기/안보이기
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
		bool bDrawDebug;

	// Socket Offset X Rate
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float SocketOffsetXRate;

	// Socket Offset Z Rate
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float SocketOffsetZRate;

	// 최대 멀어질 거리 1000이하로 해주세요.
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float MaxSocketOffDistnce;

	//락이 되어있고 마우스델타가 높으면
	UPROPERTY()
		bool bSoftlockRequiresReset;

	//카메라 잠금할 것.
	UPROPERTY(BlueprintReadOnly)
	class UTargetComponent * CameraTarget;

	ULockSpringArmComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void ToggleCameraLock();

	UFUNCTION()
		void CameraLock();

	UFUNCTION()
		void ToggleSoftLock();

	UFUNCTION()
		void LockToTarget(UTargetComponent * NewTargetComponent);

	UFUNCTION()
		void BreakTargetLock();

	UFUNCTION()
		class UTargetComponent * GetLockTarget();

	UFUNCTION()
		void SwitchTarget(EDirection SwitchDirection);

	UFUNCTION()
		TArray<class UTargetComponent*> GetTargetComponents();

	//카메라가 타켓에 락온이 되어있으면 True
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lock On Camera")
	bool IsCameraLockedToTarget();

	//레벨 시작 시 호출
	UFUNCTION(BlueprintCallable, Category = "Lock On Camera")
	void SetMaxSocketOffDistnce(float _MaxSocketOffDistnce);
};
