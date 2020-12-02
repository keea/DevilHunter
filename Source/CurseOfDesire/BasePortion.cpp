// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePortion.h"
#include "Characters/Public/MyPlayer.h"

UBasePortion::UBasePortion()
{
	isEmpty = false;
	count = 1;
	isUsed = false;
}

int UBasePortion::GetCount()
{
	return count;
}

bool UBasePortion::Execute(AMyPlayer * player)
{
	return false;
}

void UBasePortion::ResetCoolTime()
{
	UE_LOG(LogTemp, Log, TEXT("ResetCoolTime"));
	isUsed = true;
}
