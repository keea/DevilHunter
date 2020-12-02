// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Itf_AnimationNotify.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class CURSEOFDESIRE_API ACameraDirector : public AActor, public IItf_AnimationNotify
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AActor * DefaultCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	AActor * DieCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	AActor * UltimateCamera;

	UPROPERTY()
	float TimeToNextCameraChange;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_PlayerState")
	void Itf_PlayerDie();
	virtual void Itf_PlayerDie_Implementation() override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_PlayerState")
	void Itf_PlayerResurrection();
	virtual void Itf_PlayerResurrection_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_PlayerState")
	void Itf_Skill_Ultimate_Start();
	virtual void Itf_Skill_Ultimate_Start_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_PlayerState")
		void Itf_Skill_Ultimate_End();
	virtual void Itf_Skill_Ultimate_End_Implementation() override;

};
