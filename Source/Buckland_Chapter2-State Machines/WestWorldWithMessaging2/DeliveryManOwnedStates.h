#ifndef DELIVERYMAN_OWNED_STATES_H
#define DELIVERYMAN_OWNED_STATES_H
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

	virtual void Enter(DeliveryMan* wife) {}

	virtual void Execute(DeliveryMan* wife);

	virtual void Exit(DeliveryMan* wife) {}

	virtual bool OnMessage(DeliveryMan* wife, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class ArrangeParcel : public State<DeliveryMan>
{
private:

	ArrangeParcel() {}

	//copy ctor and assignment should be private
	ArrangeParcel(const ArrangeParcel&);
	ArrangeParcel& operator=(const ArrangeParcel&);

public:

	//this is a singleton
	static ArrangeParcel* Instance();

	virtual void Enter(DeliveryMan* wife);

	virtual void Execute(DeliveryMan* wife);

	virtual void Exit(DeliveryMan* wife);

	virtual bool OnMessage(DeliveryMan* wife, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DrinkWater : public State<DeliveryMan>
{
private:

	DrinkWater() {}

	//copy ctor and assignment should be private
	DrinkWater(const DrinkWater&);
	DrinkWater& operator=(const DrinkWater&);

public:

	//this is a singleton
	static DrinkWater* Instance();

	virtual void Enter(DeliveryMan* wife);

	virtual void Execute(DeliveryMan* wife);

	virtual void Exit(DeliveryMan* wife);

	virtual bool OnMessage(DeliveryMan* wife, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DeliveryToHouse : public State<DeliveryMan>
{
private:

	DeliveryToHouse() {}

	//copy ctor and assignment should be private
	DeliveryToHouse(const DeliveryToHouse&);
	DeliveryToHouse& operator=(const DeliveryToHouse&);

public:

	//this is a singleton
	static DeliveryToHouse* Instance();

	virtual void Enter(DeliveryMan* wife);

	virtual void Execute(DeliveryMan* wife);

	virtual void Exit(DeliveryMan* wife);

	virtual bool OnMessage(DeliveryMan* wife, const Telegram& msg);
};


#endif