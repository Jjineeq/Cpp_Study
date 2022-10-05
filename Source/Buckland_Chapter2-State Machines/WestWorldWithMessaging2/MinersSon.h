#ifndef MINERSSON_H
#define MINERSSON_H
//------------------------------------------------------------------------
//
//  Name: MinersSon.h
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
#include "MinersSonOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"



class MinersSon : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<MinersSon>* m_pStateMachine;

    location_type   m_Location;

    //is she presently cooking?
    bool            m_bCooking;


public:

    MinersSon(int id) :m_Location(shack),
        m_bCooking(false),
        BaseGameEntity(id)

    {
        //set up the state machine
        m_pStateMachine = new StateMachine<MinersSon>(this);

        m_pStateMachine->SetCurrentState(DoStudy::Instance());

        m_pStateMachine->SetGlobalState(SonsGlobalState::Instance());
    }

    ~MinersSon() { delete m_pStateMachine; }


    //this must be implemented
    void          Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<MinersSon>* GetFSM()const { return m_pStateMachine; }

    //----------------------------------------------------accessors
    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }

    bool          Cooking()const { return m_bCooking; }
    void          SetCooking(bool val) { m_bCooking = val; }

};

#endif
