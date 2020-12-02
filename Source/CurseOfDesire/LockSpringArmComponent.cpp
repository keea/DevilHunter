// Fill out your copyright notice in the Description page of Project Settings.


#include "LockSpringArmComponent.h"
#include "TargetComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

ULockSpringArmComponent::ULockSpringArmComponent()
{
	MaxTargetLockDistance = 750.0f;
	MaxSocketOffDistnce = 100.0f;
	bDrawDebug = true;

	//ĳ���� �� ī�޶� �Ÿ�
	TargetArmLength = 300.0f;
	bUsePawnControlRotation = true;
	bEnableCameraLag = true;
	bEnableCameraRotationLag = true;
	CameraLagSpeed = 3.f;
	CameraRotationLagSpeed = 2.f;
	CameraLagMaxDistance = 100.f;
}

void ULockSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsCameraLockedToTarget()) {
		if (bDrawDebug)
			DrawDebugSphere(GetWorld(), CameraTarget->GetComponentLocation(), 20.f, 16, FColor::Red); //Draw target point

		//���� Ÿ�ϰ� �־����� ���� �����Ѵ�.
		if ((CameraTarget->GetComponentLocation() - GetComponentLocation()).Size() >
			MaxTargetLockDistance + CameraTarget->GetScaledSphereRadius()) {

			SocketOffset.X = 0.f;
			SocketOffset.Z = 0.f;
			if (bUseSoftLock) {
				//���� �� ���ο� Ÿ������ ����.
				if (UTargetComponent * NewCameraTarget = GetLockTarget())
					LockToTarget(NewCameraTarget);
				else
					BreakTargetLock();
			}
			else
			{
				BreakTargetLock();
			}
		}
		//Ÿ�ϰ� ����������� ��Ʈ�� �� ����
		else
		{
			float targetDistance = (CameraTarget->GetComponentLocation() - GetComponentLocation()).Size();
			//1000���� �����ϰ�
			float socketOffset = MaxSocketOffDistnce - ((FMath::Min(targetDistance, 1000.f)*(MaxSocketOffDistnce / 1000.f)));
			SocketOffset.X = -(SocketOffsetXRate * socketOffset);
			SocketOffset.Z = SocketOffsetZRate * socketOffset;
			UE_LOG(LogTemp, Log, TEXT("SocketOffset :: %f , %f"), SocketOffset.X, SocketOffset.Z);
		}
	}
	else
	{
		if (bUseSoftLock) // ��ó�� ���� �ڵ����� Ÿ�϶�.
		{
			if (UTargetComponent * NewCameraTarget = GetLockTarget())
			{
				if (!bSoftlockRequiresReset) //����Ʈ���� reset�ΰ�?
					LockToTarget(NewCameraTarget);
				else //�÷��̾ ����Ʈ ���� ������ �ߴ� �� ��� ���� ���� ����� ������ �缳��.
				{
					bSoftlockRequiresReset = false;
				}
			}
		}
	}
	//Darw debug
	if (bDrawDebug) {
		for (UTargetComponent * Target : GetTargetComponents()) {
			DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), Target->GetComponentLocation(), FColor::Green);
		}

		DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), MaxTargetLockDistance, 32, FColor::Cyan);
		UKismetSystemLibrary::DrawDebugString(this, FVector::ZeroVector, bUseSoftLock ? "Soft-lock Enabled" : "Soft-lock Disabled", GetOwner(), FLinearColor::Green);

		if (bSoftlockRequiresReset)
			UKismetSystemLibrary::DrawDebugString(this, FVector(0.f, 0.f, -10.f), "Soft-lock Requires Reset", GetOwner(), FLinearColor::Green);
	}
}

void ULockSpringArmComponent::CameraLock()
{

	if (IsCameraLockedToTarget()) {
		//BreakTargetLock();
		return;
	}

	UTargetComponent* NewCameraTarget = GetLockTarget();

	if (NewCameraTarget != nullptr)
	{
		LockToTarget(NewCameraTarget);
	}
}

void ULockSpringArmComponent::ToggleCameraLock()
{
	if (bUseSoftLock)
	{
		bSoftlockRequiresReset = false;
		return;
	}

	if (IsCameraLockedToTarget()) {
		BreakTargetLock();
		return;
	}

	UTargetComponent* NewCameraTarget = GetLockTarget();

	if (NewCameraTarget != nullptr)
	{
		LockToTarget(NewCameraTarget);
	}
}

void ULockSpringArmComponent::ToggleSoftLock()
{
	bUseSoftLock = !bUseSoftLock;
	if (bUseSoftLock)
	{
		bSoftlockRequiresReset = false;
	}
	else
	{
		BreakTargetLock();
	}
}

void ULockSpringArmComponent::LockToTarget(UTargetComponent * NewTargetComponent)
{
	CameraTarget = NewTargetComponent;
	bEnableCameraRotationLag = true;
}

void ULockSpringArmComponent::BreakTargetLock()
{
	if (IsCameraLockedToTarget()) {
		CameraTarget = nullptr;
		bEnableCameraRotationLag = false;
	}
}

UTargetComponent * ULockSpringArmComponent::GetLockTarget()
{
	TArray<UTargetComponent*> AvailableTargets = GetTargetComponents();
	if (AvailableTargets.Num() == 0)
		return nullptr;

	float ClosestDotToCenter = 0.f;
	UTargetComponent* TargetComponent = nullptr;

	for (int32 i = 0; i < AvailableTargets.Num(); i++) {
		float Dot = FVector::DotProduct(GetForwardVector(), (AvailableTargets[i]->GetComponentLocation() - GetComponentLocation().GetSafeNormal()).GetSafeNormal());
		if (Dot > ClosestDotToCenter) {
			ClosestDotToCenter = Dot;
			TargetComponent = AvailableTargets[i];
		}
	}
	return TargetComponent;
}

void ULockSpringArmComponent::SwitchTarget(EDirection SwitchDirection)
{
	if (!IsCameraLockedToTarget()) return;
	TArray<UTargetComponent*> AvailableTargets = GetTargetComponents(); //�� ���� ������ ��ǥ�� ���
	if (AvailableTargets.Num() < 2) return; //���� ī�޶� ���� 1 ���� �߰� ����� �־���մϴ�.

	FVector CurrentTargetDir = (CameraTarget->GetComponentLocation() - GetComponentLocation()).GetSafeNormal();
	TArray<UTargetComponent * > ViableTargets;
	for (UTargetComponent * Target : AvailableTargets) {
		if (Target == CameraTarget) continue;

		FVector TargetDir = (Target->GetComponentLocation() - GetComponentLocation()).GetSafeNormal();
		FVector Cross = FVector::CrossProduct(CurrentTargetDir, TargetDir);

		if ((SwitchDirection == EDirection::Left && Cross.Z < 0.f) // ���� z�� ����
			|| (SwitchDirection == EDirection::Right && Cross.Z > 0.0f)) //��� z�� ������
		{
			ViableTargets.AddUnique(Target);
		}
	}

	if (ViableTargets.Num() == 0) return;

	//���� ���� ���� ���̰� ���� ���� Ÿ���� ����
	int32 BestDotIdx = 0;
	for (int32 i = 1; i < ViableTargets.Num(); i++)
	{
		float BestDot = FVector::DotProduct(CurrentTargetDir,
			(ViableTargets[BestDotIdx]->GetComponentLocation() - GetComponentLocation()).GetSafeNormal());
		float TestDot = FVector::DotProduct(CurrentTargetDir,
			(ViableTargets[i]->GetComponentLocation() - GetComponentLocation()).GetSafeNormal());

		// ������ ���������� ��ǥ ������ ������ ���� �ְ��� �۴�.
		if (TestDot > BestDot)
			BestDotIdx = i;
	}
	LockToTarget(ViableTargets[BestDotIdx]);
}

TArray<class UTargetComponent*> ULockSpringArmComponent::GetTargetComponents()
{
	TArray<UPrimitiveComponent*>TargetPrims;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { EObjectTypeQuery::ObjectTypeQuery2 }; //���� ���̳��� ������Ʈ Ÿ��

	//��� ���� ��ҿ� ���� �ߺ� �˻�
	UKismetSystemLibrary::SphereOverlapComponents(GetOwner(),
		GetComponentLocation(),
		MaxTargetLockDistance,
		ObjectTypes,
		UTargetComponent::StaticClass(),
		TArray<AActor*>{GetOwner()},
		TargetPrims);

	TArray<UTargetComponent*> TargetComps;
	for (UPrimitiveComponent * comp : TargetPrims)
	{
		TargetComps.Add(Cast<UTargetComponent>(comp));
	}

	return TargetComps;
}

bool ULockSpringArmComponent::IsCameraLockedToTarget()
{
	return CameraTarget != nullptr;
}

void ULockSpringArmComponent::SetMaxSocketOffDistnce(float _MaxSocketOffDistnce)
{
	MaxSocketOffDistnce = _MaxSocketOffDistnce;
}
