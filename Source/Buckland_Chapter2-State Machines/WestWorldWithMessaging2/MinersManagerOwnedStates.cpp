#include "MinersManagerOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersManager.h"
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

MinersMangersGlobalState* MinersMangersGlobalState::Instance()
{
    static MinersMangersGlobalState instance;

    return &instance;
}


void MinersMangersGlobalState::Execute(MinersManager* MinersManger)
{
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.1) &&
        !MinersManger->GetFSM()->isInState(*DigDiamond::Instance()))
    {
        MinersManger->GetFSM()->ChangeState(DigDiamond::Instance());
    }
}

bool MinersMangersGlobalState::OnMessage(MinersManager* MinersManger, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_HiHoneyImHome:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(MinersManger->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(MinersManger->ID()) <<
            ": Hi honey. Let me make you some of mah fine country stew";

        MinersManger->GetFSM()->ChangeState(BreakTime::Instance());
    }

    return true;

    }//end switch

    return false;
}

//-------------------------------------------------------------------------DigGold

DigGold* DigGold::Instance()
{
    static DigGold instance;

    return &instance;
}


void DigGold::Enter(MinersManager* MinersManger)
{
    cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ": Time to Work";
}


void DigGold::Execute(MinersManager* MinersManger)
{
    switch (RandInt(0, 2))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ": dig gold";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ": prepare for transportation";

        break;

    case 2:

        cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ": tidy up one's surroundings";

        break;
    }
}

void DigGold::Exit(MinersManager* MinersManger)
{
}

bool DigGold::OnMessage(MinersManager* MinersManger, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------DigDiamond

DigDiamond* DigDiamond::Instance()
{
    static DigDiamond instance;

    return &instance;
}


void DigDiamond::Enter(MinersManager* MinersManger)
{
    cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ":I found a diamond";
}


void DigDiamond::Execute(MinersManager* MinersManger)
{
    cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ": Stop digging and gather around";

    MinersManger->GetFSM()->RevertToPreviousState();
}

void DigDiamond::Exit(MinersManager* MinersManger)
{
    cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ":Let's dig this up and start over";
}


bool DigDiamond::OnMessage(MinersManager* MinersManger, const Telegram& msg)
{
    return false;
}


//------------------------------------------------------------------------BreakTime

BreakTime* BreakTime::Instance()
{
    static BreakTime instance;

    return &instance;
}


void BreakTime::Enter(MinersManager* MinersManger)
{
    //if not already cooking put the stew in the oven
    if (!MinersManger->BreakTime())
    {
        cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ":Let's take a break for about 10 minutes";

        //send a delayed message myself so that I know when to take the stew
        //out of the oven
        Dispatch->DispatchMessage(1,                  //time delay
            MinersManger->ID(),           //sender ID
            MinersManger->ID(),           //receiver ID
            Msg_BreakTime,        //msg
            NO_ADDITIONAL_INFO);

        MinersManger->SetBreakTime(true);
    }
}


void BreakTime::Execute(MinersManager* MinersManger)
{
    cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ": Aren't you tired?";
}

void BreakTime::Exit(MinersManager* MinersManger)
{
    SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ": There's a lot going on today";
}


bool BreakTime::OnMessage(MinersManager* MinersManger, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_BreakTime:
    {
        cout << "\nMessage received by " << GetNameOfEntity(MinersManger->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(MinersManger->ID()) << ":Why don't you rest a little?";

        //let hubby know the stew is ready
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
            MinersManger->ID(),
            ent_Miner_Bob,
            Msg_BreakTime,
            NO_ADDITIONAL_INFO);

        MinersManger->SetBreakTime(false);

        MinersManger->GetFSM()->ChangeState(DigGold::Instance());
    }

    return true;

    }//end switch

    return false;
}