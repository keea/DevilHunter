// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
/**
 * 
 */
class CURSEOFDESIRE_API CODMonsterState : public State<CODMonsterState>
{
public:
	CODMonsterState();
	~CODMonsterState();
};

class CURSEOFDESIRE_API Tracking : public State<Tracking>
{

};//적 발견

class CURSEOFDESIRE_API Idle : public State<Idle>
{

};//기본 상태


