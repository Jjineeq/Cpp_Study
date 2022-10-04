#ifndef DELIVERYMAN_OWNED_STATES_H
#define DELIVERYMAN_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DeliveryManOwnedStates.h
//
//  Desc:   All the states that can be assigned to the DeliveryMan class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class DeliveryMan;
struct Telegram;




//------------------------------------------------------------------------
//
//  In this state the DeliveryMan will walk to a goldmine and pick up a nugget
//  of gold. If the DeliveryMan already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class EnterMineAndDigForNugget : public State<DeliveryMan>
{
private:

	EnterMineAndDigForNugget() {}

	//copy ctor and assignment should be private
	EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
	EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);

public:

	//this is a singleton
	static EnterMineAndDigForNugget* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan);

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan);

	virtual bool OnMessage(DeliveryMan* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any nuggets he is carrying. If the 
//  DeliveryMan is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more gold
//------------------------------------------------------------------------
class VisitBankAndDepositGold : public State<DeliveryMan>
{
private:

	VisitBankAndDepositGold() {}

	//copy ctor and assignment should be private
	VisitBankAndDepositGold(const VisitBankAndDepositGold&);
	VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&);

public:

	//this is a singleton
	static VisitBankAndDepositGold* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan);

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan);

	virtual bool OnMessage(DeliveryMan* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  DeliveryMan will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSleepTilRested : public State<DeliveryMan>
{
private:

	GoHomeAndSleepTilRested() {}

	//copy ctor and assignment should be private
	GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
	GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);

public:

	//this is a singleton
	static GoHomeAndSleepTilRested* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan);

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan);

	virtual bool OnMessage(DeliveryMan* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  DeliveryMan changes location to the saloon and keeps buying Whiskey until
//  his thirst is quenched. When satisfied he returns to the goldmine
//  and resumes his quest for nuggets.
//------------------------------------------------------------------------
class QuenchThirst : public State<DeliveryMan>
{
private:

	QuenchThirst() {}

	//copy ctor and assignment should be private
	QuenchThirst(const QuenchThirst&);
	QuenchThirst& operator=(const QuenchThirst&);

public:

	//this is a singleton
	static QuenchThirst* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan);

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan);

	virtual bool OnMessage(DeliveryMan* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  this is implemented as a state blip. The DeliveryMan eats the stew, gives
//  Elsa some compliments and then returns to his previous state
//------------------------------------------------------------------------
class EatStew : public State<DeliveryMan>
{
private:

	EatStew() {}

	//copy ctor and assignment should be private
	EatStew(const EatStew&);
	EatStew& operator=(const EatStew&);

public:

	//this is a singleton
	static EatStew* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan);

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan);

	virtual bool OnMessage(DeliveryMan* agent, const Telegram& msg);
};




#endif