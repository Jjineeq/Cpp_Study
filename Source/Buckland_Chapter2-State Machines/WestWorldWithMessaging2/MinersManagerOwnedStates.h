#ifndef MINERSMANAGER_OWNED_STATES_H
#define MINERSMANAGER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinersManagerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the MinersManager class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class MinersManager;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class MinersMangersGlobalState : public State<MinersManager>
{
private:

	MinersMangersGlobalState() {}

	//copy ctor and assignment should be private
	MinersMangersGlobalState(const MinersMangersGlobalState&);
	MinersMangersGlobalState& operator=(const MinersMangersGlobalState&);

public:

	//this is a singleton
	static MinersMangersGlobalState* Instance();

	virtual void Enter(MinersManager* MinersManger) {}

	virtual void Execute(MinersManager* MinersManger);

	virtual void Exit(MinersManager* MinersManger) {}

	virtual bool OnMessage(MinersManager* MinersManger, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DigGold : public State<MinersManager>
{
private:

	DigGold() {}

	//copy ctor and assignment should be private
	DigGold(const DigGold&);
	DigGold& operator=(const DigGold&);

public:

	//this is a singleton
	static DigGold* Instance();

	virtual void Enter(MinersManager* MinersManger);

	virtual void Execute(MinersManager* MinersManger);

	virtual void Exit(MinersManager* MinersManger);

	virtual bool OnMessage(MinersManager* MinersManger, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DigDiamond : public State<MinersManager>
{
private:

	DigDiamond() {}

	//copy ctor and assignment should be private
	DigDiamond(const DigDiamond&);
	DigDiamond& operator=(const DigDiamond&);

public:

	//this is a singleton
	static DigDiamond* Instance();

	virtual void Enter(MinersManager* MinersManger);

	virtual void Execute(MinersManager* MinersManger);

	virtual void Exit(MinersManager* MinersManger);

	virtual bool OnMessage(MinersManager* MinersManger, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class BreakTime : public State<MinersManager>
{
private:

	BreakTime() {}

	//copy ctor and assignment should be private
	BreakTime(const BreakTime&);
	BreakTime& operator=(const BreakTime&);

public:

	//this is a singleton
	static BreakTime* Instance();

	virtual void Enter(MinersManager* MinersManger);

	virtual void Execute(MinersManager* MinersManger);

	virtual void Exit(MinersManager* MinersManger);

	virtual bool OnMessage(MinersManager* MinersManger, const Telegram& msg);
};


#endif