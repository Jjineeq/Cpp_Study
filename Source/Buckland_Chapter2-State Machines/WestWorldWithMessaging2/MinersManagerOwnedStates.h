#ifndef MINERSWIFE_OWNED_STATES_H
#define MINERSWIFE_OWNED_STATES_H
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
class ManagersGlobalState : public State<MinersManager>
{
private:

	ManagersGlobalState() {}

	//copy ctor and assignment should be private
	ManagersGlobalState(const ManagersGlobalState&);
	ManagersGlobalState& operator=(const ManagersGlobalState&);

public:

	//this is a singleton
	static ManagersGlobalState* Instance();

	virtual void Enter(MinersManager* manager) {}

	virtual void Execute(MinersManager* manager);

	virtual void Exit(MinersManager* manager) {}

	virtual bool OnMessage(MinersManager* manager, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoHouseWork : public State<MinersManager>
{
private:

	DoHouseWork() {}

	//copy ctor and assignment should be private
	DoHouseWork(const DoHouseWork&);
	DoHouseWork& operator=(const DoHouseWork&);

public:

	//this is a singleton
	static DoHouseWork* Instance();

	virtual void Enter(MinersManager* manager);

	virtual void Execute(MinersManager* manager);

	virtual void Exit(MinersManager* manager);

	virtual bool OnMessage(MinersManager* manager, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class VisitBathroom : public State<MinersManager>
{
private:

	VisitBathroom() {}

	//copy ctor and assignment should be private
	VisitBathroom(const VisitBathroom&);
	VisitBathroom& operator=(const VisitBathroom&);

public:

	//this is a singleton
	static VisitBathroom* Instance();

	virtual void Enter(MinersManager* manager);

	virtual void Execute(MinersManager* manager);

	virtual void Exit(MinersManager* manager);

	virtual bool OnMessage(MinersManager* manager, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class CookStew : public State<MinersManager>
{
private:

	CookStew() {}

	//copy ctor and assignment should be private
	CookStew(const CookStew&);
	CookStew& operator=(const CookStew&);

public:

	//this is a singleton
	static CookStew* Instance();

	virtual void Enter(MinersManager* manager);

	virtual void Execute(MinersManager* manager);

	virtual void Exit(MinersManager* manager);

	virtual bool OnMessage(MinersManager* manager, const Telegram& msg);
};


#endif