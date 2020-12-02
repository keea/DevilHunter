// Fill out your copyright notice in the Description page of Project Settings.


#include "MySkillSpawn03.h"
#include "MyPlayer.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BasicSkill.h"
#include "MySkillUltimate.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"

void UMySkillSpawn03::Execute(FSkillInfo info) {
	UWorld * World = GetWorld();
	if (World) {
		if (info.SkillClass) {
			APlayerController * playerController = UGameplayStatics::GetPlayerController(this, 0);
			FVector MuzzleLocation = playerController->GetPawn()->GetActorLocation();
			MuzzleLocation.Y -= 50.0f;
			MuzzleLocation.Z = 0.0f;
			FRotator MuzzleRotation = playerController->GetPawn()->GetActorRotation();
			MuzzleLocation.Y -= 50.0f;
			MuzzleLocation.Z = 0.0f;

			UWorld * World = GetWorld();
			if (World) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Instigator = NULL;
				ABasicSkill* Skill = World->SpawnActor<ABasicSkill>(info.SkillClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				Skill->Execute();
			}
		}
	}
}