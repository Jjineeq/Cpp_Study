#ifndef MINERSSON_H
#define MINERSSON_H
//------------------------------------------------------------------------
//
//  Name: MinersSon.h
//
//  Desc: class to implement Miner Bob's son.
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
    bool            m_bGoAcademy;


public:

    MinersSon(int id) :m_Location(shack),
        m_bGoAcademy(false),
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

    bool          GoAcademy()const { return m_bGoAcademy; }
    void          SetGoAcademy(bool val) { m_bGoAcademy = val; }

};

#endif
