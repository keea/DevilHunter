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

	//캐릭터 뒤 카메라 거리
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

		//만약 타켓과 멀어지면 락을 해제한다.
		if ((CameraTarget->GetComponentLocation() - GetComponentLocation()).Size() >
			MaxTargetLockDistance + CameraTarget->GetScaledSphereRadius()) {

			SocketOffset.X = 0.f;
			SocketOffset.Z = 0.f;
			if (bUseSoftLock) {
				//범위 내 새로운 타켓으로 변경.
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
		//타켓과 가까워질수록 스트링 암 조절
		else
		{
			float targetDistance = (CameraTarget->GetComponentLocation() - GetComponentLocation()).Size();
			//1000으로 조절하고
			float socketOffset = MaxSocketOffDistnce - ((FMath::Min(targetDistance, 1000.f)*(MaxSocketOffDistnce / 1000.f)));
			SocketOffset.X = -(SocketOffsetXRate * socketOffset);
			SocketOffset.Z = SocketOffsetZRate * socketOffset;
			UE_LOG(LogTemp, Log, TEXT("SocketOffset :: %f , %f"), SocketOffset.X, SocketOffset.Z);
		}
	}
	else
	{
		if (bUseSoftLock) // 근처의 적을 자동으로 타켓락.
		{
			if (UTargetComponent * NewCameraTarget = GetLockTarget())
			{
				if (!bSoftlockRequiresReset) //소프트락이 reset인가?
					LockToTarget(NewCameraTarget);
				else //플레이어가 소프트 락을 강제로 중단 한 경우 범위 내에 대상이 없으면 재설정.
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
	TArray<UTargetComponent*> AvailableTargets = GetTargetComponents(); //록 범위 내에서 목표물 얻기
	if (AvailableTargets.Num() < 2) return; //기존 카메라 대상과 1 개의 추가 대상이 있어야합니다.

	FVector CurrentTargetDir = (CameraTarget->GetComponentLocation() - GetComponentLocation()).GetSafeNormal();
	TArray<UTargetComponent * > ViableTargets;
	for (UTargetComponent * Target : AvailableTargets) {
		if (Target == CameraTarget) continue;

		FVector TargetDir = (Target->GetComponentLocation() - GetComponentLocation()).GetSafeNormal();
		FVector Cross = FVector::CrossProduct(CurrentTargetDir, TargetDir);

		if ((SwitchDirection == EDirection::Left && Cross.Z < 0.f) // 음수 z는 왼쪽
			|| (SwitchDirection == EDirection::Right && Cross.Z > 0.0f)) //양수 z는 오른쪽
		{
			ViableTargets.AddUnique(Target);
		}
	}

	if (ViableTargets.Num() == 0) return;

	//현재 대상과 각도 차이가 가장 작은 타켓을 선택
	int32 BestDotIdx = 0;
	for (int32 i = 1; i < ViableTargets.Num(); i++)
	{
		float BestDot = FVector::DotProduct(CurrentTargetDir,
			(ViableTargets[BestDotIdx]->GetComponentLocation() - GetComponentLocation()).GetSafeNormal());
		float TestDot = FVector::DotProduct(CurrentTargetDir,
			(ViableTargets[i]->GetComponentLocation() - GetComponentLocation()).GetSafeNormal());

		// 내적이 높을수록이 목표 벡터의 각도가 이전 최고보다 작다.
		if (TestDot > BestDot)
			BestDotIdx = i;
	}
	LockToTarget(ViableTargets[BestDotIdx]);
}

TArray<class UTargetComponent*> ULockSpringArmComponent::GetTargetComponents()
{
	TArray<UPrimitiveComponent*>TargetPrims;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { EObjectTypeQuery::ObjectTypeQuery2 }; //월드 다이나믹 오브젝트 타입

	//대상 구성 요소에 대한 중복 검사
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
