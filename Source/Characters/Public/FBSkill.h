// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "FBSkill.generated.h"

UCLASS()
class CHARACTERS_API AFBSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFBSkill();
	float a_scale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enermy)
		class UPrimitiveComponent* FBSkillTriggerCompoent;

	ACharacter* PlayerCharacter;
	FVector DirPos;
	FVector Playerpos;

	AActor* aoe;

	UPROPERTY(EditDefaultsOnly, Category = "FBSkill")
		TSubclassOf<AActor> RoundAOE1;
	UPROPERTY(EditDefaultsOnly, Category = "FBSkill")
		TSubclassOf<AActor> RoundAOE2;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		FVector PLoc;
	
	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBSkill")
	float TimeDelay;
	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBSkill")
	float Timer;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBSkill")
		bool m_idOverlap;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBSkill")
	bool Skillplay;
	class AMyPlayer* player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	FVector Direction;
	bool seet;
	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBSkill")
		bool ParticleType;//0 : 5 1 : 6

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBSkill")
		int skilltype;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBSkill")
		bool Berserkermode;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBSkill")
		FRotator skillRotator;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = Animation)
		float scaleSpeed;

	void SetSkillType(int type);
};
