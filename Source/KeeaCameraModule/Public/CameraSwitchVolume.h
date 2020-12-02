// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraSwitchVolume.generated.h"

class UBoxComponent;
class UTextRenderComponent;
class APlayerCamera;

UCLASS()
class KEEACAMERAMODULE_API ACameraSwitchVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraSwitchVolume();

	//components
	UBoxComponent * BoxCollsion;

	UTextRenderComponent * TextRenderNewCamera;
	UTextRenderComponent * TextRenderPreviousCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Construction Script
	virtual void OnConstruction(const FTransform& Transform);

	//Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")
	float VolumeWidth = 32.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")
	float VolumeHeight = 32.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
	APlayerCamera * NewCamera;

	//플레이어를 따라다니는 카메라로 되돌아갈 경우 비어둠.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
	APlayerCamera * PreviousCamera;

	//기본 카메라
	UPROPERTY()
	AActor * DefaultCamera;

	//Overlap Event
	UFUNCTION()
	void OnEndOverlap(class AActor* ThisActor, class AActor* OtherActor);
};
