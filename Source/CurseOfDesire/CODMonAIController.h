// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine.h"

//#include "CODMon.h"
#include "CODMonAIController.generated.h"

UCLASS()
class CURSEOFDESIRE_API ACODMonAIController : public AAIController
{
	GENERATED_BODY()


public:
	ACODMonAIController();
	/*virtual void Tick(float DeltaTime) override;*/
	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_isFindChar;

	//UPROPERTY(EditAnywhere, Category = Character)
	//	ACharacter* PlayerCharacter;//플레이어 캐릭터 찾기
};
