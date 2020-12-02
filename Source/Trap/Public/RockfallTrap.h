// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrap.h"
#include "RockfallTrap.generated.h"


UCLASS()
class TRAP_API ARockfallTrap : public ABaseTrap
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockfallTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//트랩 트리거 설정(충돌 했을 때)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//함정 발동 함수
	virtual void OnActivateTrap(class AMyPlayer * player);
};
