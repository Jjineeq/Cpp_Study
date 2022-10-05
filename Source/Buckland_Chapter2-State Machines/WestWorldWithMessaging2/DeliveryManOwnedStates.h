#ifndef DeliveryMan_OWNED_STATES_H
#define DeliveryMan_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DeliveryManOwnedStates.h
//
//  Desc:   All the states that can be assigned to the DeliveryMan class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"
using namespace std;

class DeliveryMan;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DeliveryMansGlobalState : public State<DeliveryMan>
{
private:

	DeliveryMansGlobalState() {}

	//copy ctor and assignment should be private
	DeliveryMansGlobalState(const DeliveryMansGlobalState&);
	DeliveryMansGlobalState& operator=(const DeliveryMansGlobalState&);

public:

	//this is a singleton
	static DeliveryMansGlobalState* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan) {}

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan) {}

	virtual bool OnMessage(DeliveryMan* DeliveryMan, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoHouseWork : public State<DeliveryMan>
{
private:

	DoHouseWork() {}

	//copy ctor and assignment should be private
	DoHouseWork(const DoHouseWork&);
	DoHouseWork& operator=(const DoHouseWork&);

public:

	//this is a singleton
	static DoHouseWork* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan);

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan);

	virtual bool OnMessage(DeliveryMan* DeliveryMan, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class VisitBathroom : public State<DeliveryMan>
{
private:

	VisitBathroom() {}

	//copy ctor and assignment should be private
	VisitBathroom(const VisitBathroom&);
	VisitBathroom& operator=(const VisitBathroom&);

public:

	//this is a singleton
	static VisitBathroom* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan);

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan);

	virtual bool OnMessage(DeliveryMan* DeliveryMan, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class CookStew : public State<DeliveryMan>
{
private:

	CookStew() {}

	//copy ctor and assignment should be private
	CookStew(const CookStew&);
	CookStew& operator=(const CookStew&);

public:

	//this is a singleton
	static CookStew* Instance();

	virtual void Enter(DeliveryMan* DeliveryMan);

	virtual void Execute(DeliveryMan* DeliveryMan);

	virtual void Exit(DeliveryMan* DeliveryMan);

	virtual bool OnMessage(DeliveryMan* DeliveryMan, const Telegram& msg);
};


#endif