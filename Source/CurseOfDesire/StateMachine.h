// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
/**
 * 
 */
template <typename M_Type>

class CURSEOFDESIRE_API StateMachine
{
private:
	M_Type*          m_pOwner;

	State<M_Type>*   m_pCurrentState;

	//a record of the last state the agent was in
	State<M_Type>*   m_pPreviousState;

	//this is called every time the FSM is updated
	State<M_Type>*   m_pGlobalState;

public:
	StateMachine(M_Type* owner) :m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL)
	{}

	virtual ~StateMachine() {}

	//use these methods to initialize the FSM
	void SetCurrentState(State<M_Type>* s) { m_pCurrentState = s; }
	void SetGlobalState(State<M_Type>* s) { m_pGlobalState = s; }
	void SetPreviousState(State<M_Type>* s) { m_pPreviousState = s; }

	//call this to update the FSM
	void  Update()const
	{
		if (m_pGlobalState)   m_pGlobalState->Execute(m_pOwner);//어디서나 실행가능

		if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);//현재 state와 같을 떄
	}

	//change to a new state
	void  ChangeState(State<M_Type>* pNewState)
	{
		assert(pNewState &&
			"<StateMachine::ChangeState>: trying to change to NULL state");

		//keep a record of the previous state
		m_pPreviousState = m_pCurrentState;

		//call the exit method of the existing state
		m_pCurrentState->Exit(m_pOwner);

		//change state to the new state
		m_pCurrentState = pNewState;

		//call the entry method of the new state
		m_pCurrentState->Enter(m_pOwner);
	}

	//change state back to the previous state
	void  RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool  isInState(const State<M_Type>& st)const
	{
		return typeid(*m_pCurrentState) == typeid(st);
	}

	State<M_Type>*  CurrentState()  const { return m_pCurrentState; }
	State<M_Type>*  GlobalState()   const { return m_pGlobalState; }
	State<M_Type>*  PreviousState() const { return m_pPreviousState; }
};

