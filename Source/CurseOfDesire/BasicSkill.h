// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Itf_AnimationNotify.h"
#include "GameFramework/Actor.h"
#include "BasicSkill.generated.h"

UCLASS()
class CURSEOFDESIRE_API ABasicSkill : public AActor, public IItf_AnimationNotify
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setting)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* UseSkillMontages;

	UPROPERTY()
	class ASkillManager * skillManager;

	UFUNCTION()
	virtual void Execute();

	//��ų Ʈ���� ����
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�ı��ϱ�
	UFUNCTION()
	virtual void Delete();

	//��ų ���̵�
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	int skillID;
};
