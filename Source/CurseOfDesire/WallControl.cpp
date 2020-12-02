// Fill out your copyright notice in the Description page of Project Settings.


#include "WallControl.h"
#include "Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"

// Sets default values for this component's properties
UWallControl::UWallControl()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWallControl::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//월드에 있는 엑터 검색.
	UWorld * CurrentWorld = GetWorld();

	for (const auto & Entry:FActorRange(CurrentWorld)) {
		TArray<UObject * >Components;
		Entry->GetDefaultSubobjects(Components);

		for (const auto & CEntry : Components) //순회
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Input Value : String : %s, Int : %d, Float : %f"), TEXT("Name"), 99, 3.14f));
		}
	}
}


// Called every frame
void UWallControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

