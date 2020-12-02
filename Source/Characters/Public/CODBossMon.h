// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonsterClass.h"
#include "GameFramework/Character.h"
#include "CODBossMon.generated.h"

UCLASS()
class CHARACTERS_API ACODBossMon : public ABaseMonsterClass
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACODBossMon();

	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		int currentState;

	float skill3time;
	AActor* aoe;
	bool decide;
	float skilldelay;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage * >	FBAnimMontages;//FB 애니메이션.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enermy)
		class UBoxComponent* FBTriggerCompoent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		class UBoxComponent* MeleeCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		class UBoxComponent* MeleeCollisionBox1;

	//광폭화
	void BerserkerMode();

	void DevilSpear();

	void Pattern();

	void PlaySkill2(float DeltaTime);

	void PlaySkill3();

	void PatternRotation();

	float skill2Timer;

	void playPattern();

	void Reset();

	UPROPERTY(EditDefaultsOnly, Category = "FBSkill")
		TSubclassOf<AActor> RoundAOE1;
	UPROPERTY(EditDefaultsOnly, Category = "FBSkill")
		TSubclassOf<AActor> RoundAOE2;

	UPROPERTY(EditDefaultsOnly, Category = "FBSkill")
		TSubclassOf<AActor>PlaySkill02;

	UPROPERTY(EditDefaultsOnly, Category = "FBSkill")
		TSubclassOf<AActor>PlaySkill5;

	UPROPERTY(EditDefaultsOnly, Category = "FBSkill")
		TSubclassOf<AActor>PlaySkill6;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		int PatternTime;//광폭화시 시간 줄어들기

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool isBerserker;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool playParticle;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool evasion;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "Play")
		float PlayLimt;

	//스킬 확인
	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool skill1;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool skill2;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool skill3;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool skill4;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool skill5;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool skill6;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool faint;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		bool checkPlay;

	//UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
	//	bool PlayParticle;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		int skill4Count;//1과 2 다름

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		int PatternIndex;

	UPROPERTY(EditAnywhere, blueprintreadwrite, Category = "FBPattern")
		float LimitDir;



	//애니메이션 재생
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill1_Start();
	virtual void Itf_FBSkill1_Start_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill2_Start();
	virtual void Itf_FBSkill2_Start_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill3_Start();
	virtual void Itf_FBSkill3_Start_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill4_Start();
	virtual void Itf_FBSkill4_Start_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill4_End();
	virtual void Itf_FBSkill4_End_Implementation() override;

	//스킬 4 애니메이션이 끝났다는 것을 블루프린터에 이벤트 보내기
	UFUNCTION(BlueprintNativeEvent)
	void FBSkill4_End();
	virtual void FBSkill4_End_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill5_Start();
	virtual void Itf_FBSkill5_Start_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill5_End();
	virtual void Itf_FBSkill5_End_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill6_Start();
	virtual void Itf_FBSkill6_Start_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_AnimState")
		void Itf_FBSkill6_End();
	virtual void Itf_FBSkill6_End_Implementation() override;

	UFUNCTION(BlueprintCallable)
		void Skill01();

	UFUNCTION(BlueprintCallable)
		void Skill02();

	UFUNCTION(BlueprintCallable)
		void Skill03();

	UFUNCTION(BlueprintCallable)
		void Skill04_Fir();

	UFUNCTION(BlueprintCallable)
		void Skill04_End();

	UFUNCTION(BlueprintCallable)
		void Skill04_Sec();

	UFUNCTION(BlueprintCallable)
		void Skill05();

	UFUNCTION(BlueprintCallable)
		void Skill05End();

	UFUNCTION(BlueprintCallable)
		void Skill06();

	UFUNCTION(BlueprintCallable)
		void Skill06End();

private:
	UPROPERTY()
	class USingletonObject *  instance;
};
