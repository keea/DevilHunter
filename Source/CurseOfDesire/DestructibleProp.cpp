// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleProp.h"
#include "Engine.h"
#include "MyPlayer.h"

// Sets default values
ADestructibleProp::ADestructibleProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Compoent"));

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destrcutible Component"));
	DestructibleComponent->SetupAttachment(RootComponent);
	DestructibleComponent->SetNotifyRigidBodyCollision(true);

	TriggerCompoent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger compoent"));
	TriggerCompoent->SetupAttachment(RootComponent);
	TriggerCompoent->SetHiddenInGame(false);

	m_isDestoryed = false;
	m_isTriggerEnabled = false;

	m_maxHealth = 1.f;
	m_defaultImpulse = 1.f;
}

void ADestructibleProp::Damage(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{

}

void ADestructibleProp::Trigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	if (!m_isDestoryed && OtherComp->ComponentHasTag("Weapon")) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, __FUNCTION__);
		AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
		
		if (player && player->GetIsAttack()) { //플레이어가 null이 아니고 공격상태일 경우
			//이벤트를 호출 시킨다.
			TriggerEnterPlayerAttack(player->GetATK());
			m_currentHealth = m_currentHealth - player->GetATK(); //hp를 감소시킨다.
			if (m_currentHealth <= 0.f) { //hp가 0라면
				Destroy(m_Defaultdamage, DestructibleComponent->GetComponentLocation(), DestructibleComponent->GetForwardVector(), m_defaultImpulse); //파괴시키기.
				player->SetFringe(true);
			}
		}
	}
}

void ADestructibleProp::Destroy(float Damage, FVector HitLocation, FVector  ImpulseDir, float Impulse)
{
	
	if (!m_isDestoryed) {

		m_isDestoryed = true;
		DestructibleComponent->ApplyDamage(m_Defaultdamage, HitLocation, ImpulseDir, m_defaultImpulse);
		//트리거 컴포넌트를 삭제한다.
		TriggerCompoent->DestroyComponent();
	}
}

void ADestructibleProp::DestructibleTrigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

// Called when the game starts or when spawned
void ADestructibleProp::BeginPlay()
{
	Super::BeginPlay();
	TriggerCompoent->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleProp::Trigger);
	m_currentHealth = m_maxHealth;
}

// Called every frame
void ADestructibleProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestructibleProp::TriggerEnterPlayerAttack_Implementation(int damage)
{
}

