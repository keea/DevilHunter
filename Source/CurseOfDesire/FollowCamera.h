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

	//타겟 액터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	AActor * TargetActor;

	//조종할 카메라.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	AActor * DefaultCamera;

	//초기 카메라 간격 IntervalVectorShow에 보여진 값을 입력해주세요.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	FVector IntervalVector;
	
	//카메라 위치를 세팅하고 확인해주세요.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	FVector IntervalVectorShow;
};
