#include "MinersSon.h"
#include "MinersSonOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWifeOwnedStates.h"
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
    if ((RandFloat() < 0.2) &&
        !son->GetFSM()->isInState(*TakeARest::Instance()))
    {
        son->GetFSM()->ChangeState(TakeARest::Instance());
    }
}



//-------------------------------------------------------------------------DoStudy

DoStudy* DoStudy::Instance()
{
  static DoStudy instance;

  return &instance;
}


void DoStudy::Enter(MinersSon* son)
{
  cout << "\n" << GetNameOfEntity(son->ID()) << ": Time to do some more Study!";
}


void DoStudy::Execute(MinersSon* son)
{
    switch (RandInt(0, 2))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Study Math";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Study English";

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
    cout << "\n" << GetNameOfEntity(son->ID()) << ": I'll need some rest";
}


void TakeARest::Execute(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": What a nice time";

    son->GetFSM()->RevertToPreviousState();
}

void TakeARest::Exit(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Return to Study";
}


bool TakeARest::OnMessage(MinersSon* son, const Telegram& msg)
{
    return false;
}


