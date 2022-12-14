#ifndef MINERSMANGER_H
#define MINERSMANGER_H
//------------------------------------------------------------------------
//
//  Name: MinersManager.h
//
//  Desc: class to implement Miner Bob's MinersManger.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "MinersManagerOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"



class MinersManager : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<MinersManager>* m_pStateMachine;

    location_type   m_Location;

    //is she presently cooking?
    bool            m_bBreakTime;


public:

    MinersManager(int id) :m_Location(shack),
        m_bBreakTime(false),
        BaseGameEntity(id)

    {
        //set up the state machine
        m_pStateMachine = new StateMachine<MinersManager>(this);

        m_pStateMachine->SetCurrentState(DigGold::Instance());

        m_pStateMachine->SetGlobalState(MinersMangersGlobalState::Instance());
    }

    ~MinersManager() { delete m_pStateMachine; }


    //this must be implemented
    void          Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<MinersManager>* GetFSM()const { return m_pStateMachine; }

    //----------------------------------------------------accessors
    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }

    bool          BreakTime()const { return m_bBreakTime; }
    void          SetBreakTime(bool val) { m_bBreakTime = val; }

};

#endif
