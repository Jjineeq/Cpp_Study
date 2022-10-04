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

ManagersGlobalState* ManagersGlobalState::Instance()
{
    static ManagersGlobalState instance;

    return &instance;
}


void ManagersGlobalState::Execute(MinersManager* manager)
{
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.1) &&
        !manager->GetFSM()->isInState(*VisitBathroom::Instance()))
    {
        manager->GetFSM()->ChangeState(VisitBathroom::Instance());
    }
}

bool ManagersGlobalState::OnMessage(MinersManager* manager, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_HiHoneyImHome:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(manager->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(manager->ID()) <<
            ": Hi honey. Let me make you some of mah fine country stew";

        manager->GetFSM()->ChangeState(CookStew::Instance());
    }

    return true;

    }//end switch

    return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHouseWork* DoHouseWork::Instance()
{
    static DoHouseWork instance;

    return &instance;
}


void DoHouseWork::Enter(MinersManager* manager)
{
    cout << "\n" << GetNameOfEntity(manager->ID()) << ": Time to do some more housework!";
}


void DoHouseWork::Execute(MinersManager* manager)
{
    switch (RandInt(0, 2))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(manager->ID()) << ": Moppin' the floor";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(manager->ID()) << ": Washin' the dishes";

        break;

    case 2:

        cout << "\n" << GetNameOfEntity(manager->ID()) << ": Makin' the bed";

        break;
    }
}

void DoHouseWork::Exit(MinersManager* manager)
{
}

bool DoHouseWork::OnMessage(MinersManager* manager, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathroom* VisitBathroom::Instance()
{
    static VisitBathroom instance;

    return &instance;
}


void VisitBathroom::Enter(MinersManager* manager)
{
    cout << "\n" << GetNameOfEntity(manager->ID()) << ": Walkin' to the can. Need to powda mah pretty li'lle nose";
}


void VisitBathroom::Execute(MinersManager* manager)
{
    cout << "\n" << GetNameOfEntity(manager->ID()) << ": Ahhhhhh! Sweet relief!";

    manager->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersManager* manager)
{
    cout << "\n" << GetNameOfEntity(manager->ID()) << ": Leavin' the Jon";
}


bool VisitBathroom::OnMessage(MinersManager* manager, const Telegram& msg)
{
    return false;
}


//------------------------------------------------------------------------CookStew

CookStew* CookStew::Instance()
{
    static CookStew instance;

    return &instance;
}


void CookStew::Enter(MinersManager* manager)
{
    //if not already cooking put the stew in the oven
    if (!manager->Cooking())
    {
        cout << "\n" << GetNameOfEntity(manager->ID()) << ": Putting the stew in the oven";

        //send a delayed message myself so that I know when to take the stew
        //out of the oven
        Dispatch->DispatchMessage(1.5,                  //time delay
            manager->ID(),           //sender ID
            manager->ID(),           //receiver ID
            Msg_StewReady,        //msg
            NO_ADDITIONAL_INFO);

        manager->SetCooking(true);
    }
}


void CookStew::Execute(MinersManager* manager)
{
    cout << "\n" << GetNameOfEntity(manager->ID()) << ": Fussin' over food";
}

void CookStew::Exit(MinersManager* manager)
{
    SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    cout << "\n" << GetNameOfEntity(manager->ID()) << ": Puttin' the stew on the table";
}


bool CookStew::OnMessage(MinersManager* manager, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_StewReady:
    {
        cout << "\nMessage received by " << GetNameOfEntity(manager->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(manager->ID()) << ": StewReady! Lets eat";

        //let hubby know the stew is ready
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
            manager->ID(),
            ent_Miner_Bob,
            Msg_StewReady,
            NO_ADDITIONAL_INFO);

        manager->SetCooking(false);

        manager->GetFSM()->ChangeState(DoHouseWork::Instance());
    }

    return true;

    }//end switch

    return false;
}