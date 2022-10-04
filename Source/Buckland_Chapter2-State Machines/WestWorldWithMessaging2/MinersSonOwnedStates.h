#ifndef MINERSWIFE_OWNED_STATES_H
#define MINERSWIFE_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinersSonOwnedStates.h
//
//  Desc:   All the states that can be assigned to the MinersSon class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class MinersSon;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class SonsGlobalState : public State<MinersSon>
{
private:

	SonsGlobalState() {}

	//copy ctor and assignment should be private
	SonsGlobalState(const SonsGlobalState&);
	SonsGlobalState& operator=(const SonsGlobalState&);

public:

	//this is a singleton
	static SonsGlobalState* Instance();

	virtual void Enter(MinersSon* son) {}

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son) {}

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoHouseWork : public State<MinersSon>
{
private:

	DoHouseWork() {}

	//copy ctor and assignment should be private
	DoHouseWork(const DoHouseWork&);
	DoHouseWork& operator=(const DoHouseWork&);

public:

	//this is a singleton
	static DoHouseWork* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class VisitBathroom : public State<MinersSon>
{
private:

	VisitBathroom() {}

	//copy ctor and assignment should be private
	VisitBathroom(const VisitBathroom&);
	VisitBathroom& operator=(const VisitBathroom&);

public:

	//this is a singleton
	static VisitBathroom* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class CookStew : public State<MinersSon>
{
private:

	CookStew() {}

	//copy ctor and assignment should be private
	CookStew(const CookStew&);
	CookStew& operator=(const CookStew&);

public:

	//this is a singleton
	static CookStew* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);
};


#endif