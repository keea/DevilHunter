// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"

#include "DestructibleProp.generated.h"

UCLASS()
class CURSEOFDESIRE_API ADestructibleProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleProp();

	UFUNCTION()
	void Damage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void Destroy(float Damage, FVector HitLocation, FVector  ImpulseDir, float Impulse);
	UFUNCTION()
	void DestructibleTrigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible)
	class UBoxComponent* TriggerCompoent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible)
	class UDestructibleComponent * DestructibleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	bool m_isTriggerEnabled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	bool m_isDestoryed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	float m_maxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible)
	float m_currentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	float m_Defaultdamage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	float m_defaultImpulse;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector m_vecDefaultLocation; //기본 위치값

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//플레이어가 공격을 해서 맞았을 때
	UFUNCTION(BlueprintNativeEvent)
	void TriggerEnterPlayerAttack(int damage);
	virtual void TriggerEnterPlayerAttack_Implementation(int damage);
};
