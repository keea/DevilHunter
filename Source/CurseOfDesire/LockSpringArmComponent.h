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
UCLASS(meta = (BlueprintSpawnableComponent)) //�������Ʈ�� ������Ʈ Ŭ������ ����.
class CURSEOFDESIRE_API ULockSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()
	
public:
	// Ÿ������ ���� �ִ� �Ÿ�.
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
		float MaxTargetLockDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
		bool bUseSoftLock;

	// ����� ���̱�/�Ⱥ��̱�
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
		bool bDrawDebug;

	// Socket Offset X Rate
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float SocketOffsetXRate;

	// Socket Offset Z Rate
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float SocketOffsetZRate;

	// �ִ� �־��� �Ÿ� 1000���Ϸ� ���ּ���.
	UPROPERTY(EditDefaultsOnly, Category = "Lock On Camera")
	float MaxSocketOffDistnce;

	//���� �Ǿ��ְ� ���콺��Ÿ�� ������
	UPROPERTY()
		bool bSoftlockRequiresReset;

	//ī�޶� ����� ��.
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

	//ī�޶� Ÿ�Ͽ� ������ �Ǿ������� True
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lock On Camera")
	bool IsCameraLockedToTarget();

	//���� ���� �� ȣ��
	UFUNCTION(BlueprintCallable, Category = "Lock On Camera")
	void SetMaxSocketOffDistnce(float _MaxSocketOffDistnce);
};
