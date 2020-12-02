// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicSkill.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "Engine.h"
#include "CODMon.h"
#include "SkillManager.h"
#include "Engine/Engine.h"
#include "Animation/AnimMontage.h"

// Sets default values
ABasicSkill::ABasicSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = CollisionBox;

	skillID = 0;
}

// Called when the game starts or when spawned
void ABasicSkill::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABasicSkill::OnOverlapBegin);
	for (TActorIterator<ASkillManager> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		skillManager = Cast<ASkillManager>(*ActorItr);
		if (skillManager) {
			break;
		}
	}
}

void ABasicSkill::Execute()
{

}

void ABasicSkill::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("enemy")) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("MBHit"));
		ABaseMonsterClass * moster = Cast<ABaseMonsterClass>(OtherActor);
		if (!moster)
			return;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, __FUNCTION__);
		if (moster->GetClass()->ImplementsInterface(UItf_AnimationNotify::StaticClass()) == true)
			IItf_AnimationNotify::Execute_Itf_Skill_Damage(moster, skillManager->SkillInfo[skillID].Damage);
	}
}

// Called every frame
void ABasicSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicSkill::Delete()
{
	Destroy();
}

