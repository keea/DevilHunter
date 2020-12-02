// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "CurseOfDesire.h"
#include "testChar.h"


void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();
	//DefaultPawnClass = AtestChar::StaticClass();

	//if (GEngine)
	//{
	//	// Display a debug message for five seconds. 
	//	// The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	//}
}
