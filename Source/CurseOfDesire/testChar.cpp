// Fill out your copyright notice in the Description page of Project Settings.


#include "testChar.h"
#include "CurseOfDesire.h"
#include "Engine.h"

// Sets default values
AtestChar::AtestChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AtestChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AtestChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttackCheck();
}

// Called to bind functionality to input
void AtestChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AtestChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AtestChar::MoveRight);
}

void AtestChar::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gogogo"));
	}
	
}

void AtestChar::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}

}

void AtestChar::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + GetActorForwardVector()*200.0f, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12, FCollisionShape::MakeSphere(50.0f), Params);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("PATK"));
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}

float AtestChar::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);			
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("PHit"));


	if (FinalDamage > 0.0f)
	{
		//ABAnim->SetDeadAnim();
		//SetActorEnableCollision(false);
	}

	return FinalDamage;
}
