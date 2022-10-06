#ifndef DELIVERYMAN_H
#define DELIVERYMAN_H
//------------------------------------------------------------------------
//
//  Name: DeliveryMan.h
//
//  Desc: class to implement Miner Bob's Son.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "DeliveryManOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"



class DeliveryMan : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<DeliveryMan>* m_pStateMachine;

    location_type   m_Location;

    //is she presently Delivery?
    bool            m_bDelivery;


public:

    DeliveryMan(int id) :m_Location(shack),
        m_bDelivery(false),
        BaseGameEntity(id)

    {
        //set up the state machine
        m_pStateMachine = new StateMachine<DeliveryMan>(this);

        m_pStateMachine->SetCurrentState(ArrangeParcel::Instance());

        m_pStateMachine->SetGlobalState(DeliveryMansGlobalState::Instance());
    }

    ~DeliveryMan() { delete m_pStateMachine; }


    //this must be implemented
    void          Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<DeliveryMan>* GetFSM()const { return m_pStateMachine; }

    //----------------------------------------------------accessors
    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }

    bool          Delivery()const { return m_bDelivery; }
    void          SetDelivery(bool val) { m_bDelivery = val; }

};

#endif
