// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "StateMachine.h"
#include "CODMon.h"
#include "MyPlayer.h"

/**
 * 
 */
class CURSEOFDESIRE_API CODMonStates
{

public:
	CODMonStates();
	~CODMonStates();
};

//캐릭터와 몬스터의 위치를 계산하고 조건이 달성되면 Chase로 바꾼다.-> 조건 달성은 CODmon으로
class CURSEOFDESIRE_API IDLE : public State<ACODMon>, ABasicCharacterClass
{
private:
	IDLE() {};
	IDLE(const IDLE&);
	IDLE& operator=(const IDLE&);

public:
	static IDLE* Instance();

	virtual void Enter(ACODMon* mon);

	virtual void Execute(ACODMon* mon);

	virtual void Exit(ACODMon* mon);
};