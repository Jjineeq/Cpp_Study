#include "MinersSonOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersSon.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

SonsGlobalState* SonsGlobalState::Instance()
{
    static SonsGlobalState instance;

    return &instance;
}


void SonsGlobalState::Execute(MinersSon* son)
{
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.1) &&
        !son->GetFSM()->isInState(*TakeARest::Instance()))
    {
        son->GetFSM()->ChangeState(TakeARest::Instance());
    }
}

bool SonsGlobalState::OnMessage(MinersSon* son, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_HiHoneyImHome:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(son->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(son->ID()) <<
            ": Hi honey. Let me make you some of mah fine country stew";

        son->GetFSM()->ChangeState(GoAcademy::Instance());
    }

    return true;

    }//end switch

    return false;
}

//-------------------------------------------------------------------------DoStudy

DoStudy* DoStudy::Instance()
{
    static DoStudy instance;

    return &instance;
}


void DoStudy::Enter(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Time to Study";
}


void DoStudy::Execute(MinersSon* son)
{
    switch (RandInt(0, 2))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Study English";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Study Math";

        break;

    case 2:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Study Physics";

        break;
    }
}

void DoStudy::Exit(MinersSon* son)
{
}

bool DoStudy::OnMessage(MinersSon* son, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------TakeARest

TakeARest* TakeARest::Instance()
{
    static TakeARest instance;

    return &instance;
}


void TakeARest::Enter(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": It's time to rest";
}


void TakeARest::Execute(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": I'll take a rest to 5 minutes";

    son->GetFSM()->RevertToPreviousState();
}

void TakeARest::Exit(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": It time to back";
}


bool TakeARest::OnMessage(MinersSon* son, const Telegram& msg)
{
    return false;
}


//------------------------------------------------------------------------GoAcademy

GoAcademy* GoAcademy::Instance()
{
    static GoAcademy instance;

    return &instance;
}


void GoAcademy::Enter(MinersSon* son)
{
    //if not already cooking put the stew in the oven
    if (!son->GoAcademy())
    {
        cout << "\n" << GetNameOfEntity(son->ID()) << ": StewReady! Lets eat";

        //send a delayed message myself so that I know when to take the stew
        //out of the oven
        Dispatch->DispatchMessage(0.5,                  //time delay
            son->ID(),           //sender ID
            son->ID(),           //receiver ID
            Msg_GoAcademy,        //msg
            NO_ADDITIONAL_INFO);

        son->SetGoAcademy(true);
    }
}


void GoAcademy::Execute(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": It's time to go academy";
}

void GoAcademy::Exit(MinersSon* son)
{
    SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    cout << "\n" << GetNameOfEntity(son->ID()) << ": leave the house";
}


bool GoAcademy::OnMessage(MinersSon* son, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_GoAcademy:
    {
        cout << "\nMessage received by " << GetNameOfEntity(son->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(son->ID()) << ": I'll go to the academy";

        //let hubby know the stew is ready
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
            son->ID(),
            ent_Elsa,
            Msg_GoAcademy,
            NO_ADDITIONAL_INFO);

        son->SetGoAcademy(false);

        son->GetFSM()->ChangeState(DoStudy::Instance());
    }

    return true;

    }//end switch

    return false;
}