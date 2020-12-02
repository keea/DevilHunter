// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FollowCamera.generated.h"

UCLASS()
class CURSEOFDESIRE_API AFollowCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFollowCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Ÿ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	AActor * TargetActor;

	//������ ī�޶�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	AActor * DefaultCamera;

	//�ʱ� ī�޶� ���� IntervalVectorShow�� ������ ���� �Է����ּ���.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	FVector IntervalVector;
	
	//ī�޶� ��ġ�� �����ϰ� Ȯ�����ּ���.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	FVector IntervalVectorShow;
};
