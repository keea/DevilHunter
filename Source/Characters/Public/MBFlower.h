// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonsterClass.h"
#include "MBFlower.generated.h"

UCLASS()
class CHARACTERS_API AMBFlower : public ABaseMonsterClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMBFlower();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int atkcount;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool Alive;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBFlower")
		float DeleteTime;

	/*UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "MBFlower")
		float DeleteTime;*/

	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
