// Fill out your copyright notice in the Description page of Project Settings.


#include "MySkill02.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMySkill02::AMySkill02() {
	InitialLifeSpan = 0.5f;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionBox);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
}

// Called when the game starts or when spawned
void AMySkill02::BeginPlay()
{
	Super::BeginPlay();
}

void AMySkill02::FireInDirection(const FVector & ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AMySkill02::Execute()
{
	APlayerController * playerController = UGameplayStatics::GetPlayerController(this, 0);
	FVector LaunchDirection = playerController->GetPawn()->GetActorForwardVector();
	FireInDirection(LaunchDirection);
}
