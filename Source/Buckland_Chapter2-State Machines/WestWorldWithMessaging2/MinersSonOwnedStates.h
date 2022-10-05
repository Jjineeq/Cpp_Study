#ifndef MINERSSON_OWNED_STATES_H
#define MINERSSON_OWNED_STATES_H
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
class DoStudy : public State<MinersSon>
{
private:

	DoStudy() {}

	//copy ctor and assignment should be private
	DoStudy(const DoStudy&);
	DoStudy& operator=(const DoStudy&);

public:

	//this is a singleton
	static DoStudy* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class TakeARest : public State<MinersSon>
{
private:

	TakeARest() {}

	//copy ctor and assignment should be private
	TakeARest(const TakeARest&);
	TakeARest& operator=(const TakeARest&);

public:

	//this is a singleton
	static TakeARest* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);

};


#endif