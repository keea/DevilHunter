// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowCamera.h"

// Sets default values
AFollowCamera::AFollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFollowCamera::BeginPlay()
{
	Super::BeginPlay();
	IntervalVectorShow = TargetActor->GetActorTransform().GetLocation() - DefaultCamera->GetActorTransform().GetLocation();
	if(IntervalVector == FVector::ZeroVector)
		IntervalVector = IntervalVectorShow;
	
}

// Called every frame
void AFollowCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FTransform targetTransform = TargetActor->GetActorTransform();
	FVector changeTransform = targetTransform.GetLocation() - IntervalVector;
	
	FTransform newTransform = DefaultCamera->GetTransform();
	newTransform.SetLocation(changeTransform);
	DefaultCamera->SetActorTransform(newTransform);
}

