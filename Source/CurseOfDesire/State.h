// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template <typename M_Type>
class CURSEOFDESIRE_API State
{
public:
	virtual ~State() {}

	virtual void Enter(M_Type* m) = 0;//�ֱ�

	virtual void Execute(M_Type* m) = 0;//����

	virtual void Exit(M_Type* m) = 0;//����
};