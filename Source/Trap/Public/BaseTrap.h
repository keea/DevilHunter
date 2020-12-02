// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTrap.generated.h"

UCLASS()
class TRAP_API ABaseTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//트랩 트리거 설정(충돌 했을 때)
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//벗어 났을 때.
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//트랩 파티클이 종료했을 때
	UFUNCTION()
	void OnTrapEffectFinished(class UParticleSystemComponent* PSystem);

	//트랩 관련 쿨타임.
	UPROPERTY()
	FTimerHandle m_ActivateTrapTimer;

	//함정 위에 있는지 체크
	UPROPERTY()
	bool isOnTrap;

	//함정 발동 함수
	UFUNCTION()
	virtual void OnActivateTrap(class AMyPlayer * player) {};

public:
	//나이아가라 이펙트를 사용하는가?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trap)
	bool isUseNiagaraEffect;

	//함정 관련 콜라이더 박스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trap)
		class UBoxComponent* TrapCollisionBox;

	//데미지 입히기까지 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trap)
		float DamageDelayTime;

	//데미지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trap)
		float Damage;

	//파티클 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UParticleSystemComponent* TrapEffectComponent;

	//함정 발동 파티클
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trap, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem * TrapEffect;

	//범위 표시 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Trap, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem * PlayerEnterEffect;

	//파티클 컴포넌트(범위 표시)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* PlayerEnterEffectComponent;

	////나이아가라 이펙트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trap, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* TrapNiagaraEffect;

	////파티클 컴포넌트(범위 표시)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UNiagaraComponent* TrapNiagaraEffectComponent;

	//트랩 파티클이 종료했을 때
	UFUNCTION()
	void OnTrapNiagaraEffectFinished(class UNiagaraComponent* PSystem);
};
