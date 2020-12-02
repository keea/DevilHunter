// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonsterClass.h"
#include "GameFramework/Character.h"
#include "testMon.generated.h"

UCLASS()
class CHARACTERS_API AtestMon : public ABaseMonsterClass
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AtestMon();
	/*UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree *MonBehavior;*/
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void ExplosionDemage();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		class UBoxComponent* MeleeCollisionBox;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool m_bomTimeCheck;//기절 시간

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		bool skillHit;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_MonHIT_End();
	virtual void Itf_MonHIT_End_Implementation() override;
	//void Itf_MonHIT_End();
};
