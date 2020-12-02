// Fill out your copyright notice in the Description page of Project Settings.


#include "CODMonAIController.h"
#include "MyPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "testMon.h"
#include "CurseOfDesire.h"

ACODMonAIController::ACODMonAIController()
{
	
}

//void ACODMonAIController::Tick(float DeltaTime)
//{
//	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
//	AMyPlayer* player = Cast<AMyPlayer>(PlayerCharacter);
//
//	if (player->GetHP() <= 0)
//	{
//		m_isFindChar = false;
//	}
//}