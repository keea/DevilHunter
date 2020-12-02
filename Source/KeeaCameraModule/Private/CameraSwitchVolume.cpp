// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwitchVolume.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "PlayerCamera.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraSwitchVolume::ACameraSwitchVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Box Collsion
	BoxCollsion = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollsion;
	BoxCollsion->SetBoxExtent(FVector(1.5f, 32.0f, 32.0f));

	//Set up Text Renders
	TextRenderNewCamera = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render New Camera"));
	TextRenderNewCamera->SetupAttachment(RootComponent);
	TextRenderNewCamera->SetText("New Camera Side");
	TextRenderNewCamera->SetHiddenInGame(true);
	TextRenderNewCamera->SetRelativeLocation(FVector(15.0f, 0.0f, 0.0f));
	TextRenderNewCamera->SetHorizontalAlignment(EHTA_Center);
	TextRenderNewCamera->SetVerticalAlignment(EVRTA_TextCenter);

	TextRenderPreviousCamera = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Previous New Camera"));
	TextRenderPreviousCamera->SetupAttachment(RootComponent);
	TextRenderPreviousCamera->SetText("Previous Camera Side");
	TextRenderPreviousCamera->SetHiddenInGame(true);
	TextRenderPreviousCamera->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
	TextRenderPreviousCamera->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	TextRenderPreviousCamera->SetHorizontalAlignment(EHTA_Center);
	TextRenderPreviousCamera->SetVerticalAlignment(EVRTA_TextCenter);
}

// Called when the game starts or when spawned
void ACameraSwitchVolume::BeginPlay()
{
	Super::BeginPlay();
	
	//Bind OverLap Event
	OnActorEndOverlap.AddDynamic(this, &ACameraSwitchVolume::OnEndOverlap);

	//되돌아갈 카메라가 null일 경우
	if (!PreviousCamera) 
	{
		DefaultCamera = (AActor *)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	}
}

// Called every frame
void ACameraSwitchVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACameraSwitchVolume::OnConstruction(const FTransform & Transform)
{
	BoxCollsion->SetBoxExtent(FVector(1.5f, VolumeWidth, VolumeHeight));
}

void ACameraSwitchVolume::OnEndOverlap(AActor * ThisActor, AActor * OtherActor)
{
	ACharacter * PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerController * PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FViewTargetTransitionParams TransitionParams;

	//Toggle camera based on players x relative location
	if (PlayerCharacter && OtherActor == PlayerCharacter && PlayerController) 
	{
		FVector PlayerRelativeLocation = GetTransform().InverseTransformPosition(PlayerCharacter->GetActorLocation());
		if (NewCamera && PlayerRelativeLocation.X > 0) //If player exits new camera side
		{
			PlayerController->SetIgnoreLookInput(true);
			PlayerController->SetViewTarget(NewCamera, TransitionParams);
		}

		if (PreviousCamera && PlayerRelativeLocation.X < 0) //If player exits prevous camera side
		{
			PlayerController->SetIgnoreLookInput(true);

			PlayerController->SetViewTarget(PreviousCamera, TransitionParams);
		}

		if (!PreviousCamera && PlayerRelativeLocation.X < 0) //If player not exits prevous camera side
		{ 
			PlayerController->SetIgnoreLookInput(false);

			PlayerController->SetViewTarget(DefaultCamera, TransitionParams);
		}
	}
}