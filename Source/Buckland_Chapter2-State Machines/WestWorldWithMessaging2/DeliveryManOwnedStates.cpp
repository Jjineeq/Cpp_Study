#include "DeliveryManOwnedStates.h"
#include "MinerOwnedStates.h"
#include "DeliveryMan.h"
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

DeliveryMansGlobalState* DeliveryMansGlobalState::Instance()
{
  static DeliveryMansGlobalState instance;

  return &instance;
}


void DeliveryMansGlobalState::Execute(DeliveryMan* DeliveryMan)
{
  //1 in 10 chance of needing the bathroom (provided she is not already
  //in the bathroom)
  if ( (RandFloat() < 0.1) && 
       !DeliveryMan->GetFSM()->isInState(*DeliveryToHouse::Instance()) )
  {
    DeliveryMan->GetFSM()->ChangeState(DeliveryToHouse::Instance());
  }
}

bool DeliveryMansGlobalState::OnMessage(DeliveryMan* DeliveryMan, const Telegram& msg)
{
  SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case Msg_HiHoneyImHome:
   {
       cout << "\nMessage handled by " << GetNameOfEntity(DeliveryMan->ID()) << " at time: " 
       << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << 
          ": Hi honey. Let me make you some of mah fine country stew";

     DeliveryMan->GetFSM()->ChangeState(DeliveryToHouse::Instance());
   }

   return true;

  }//end switch

  return false;
}

//-------------------------------------------------------------------------ArrangeParcel

ArrangeParcel* ArrangeParcel::Instance()
{
  static ArrangeParcel instance;

  return &instance;
}


void ArrangeParcel::Enter(DeliveryMan* DeliveryMan)
{
  cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": It's time for logistics";
}


void ArrangeParcel::Execute(DeliveryMan* DeliveryMan)
{
  switch(RandInt(0,2))
  {
  case 0:

    cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": Let's drop off the goods";

    break;

  case 1:

    cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": Let's get on board";

    break;

  case 2:

    cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": Let's sort things out";

    break;
  }
}

void ArrangeParcel::Exit(DeliveryMan* DeliveryMan)
{
}

bool ArrangeParcel::OnMessage(DeliveryMan* DeliveryMan, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------DrinkWater

DrinkWater* DrinkWater::Instance()
{
  static DrinkWater instance;

  return &instance;
}


void DrinkWater::Enter(DeliveryMan* DeliveryMan)
{  
  cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": Let's drink water and rest"; 
}


void DrinkWater::Execute(DeliveryMan* DeliveryMan)
{
  cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": find cool water";

  DeliveryMan->GetFSM()->RevertToPreviousState();
}

void DrinkWater::Exit(DeliveryMan* DeliveryMan)
{
  cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": done drinking, so I'll keep going";
}


bool DrinkWater::OnMessage(DeliveryMan* DeliveryMan, const Telegram& msg)
{
  return false;
}


//------------------------------------------------------------------------DeliveryToHouse

DeliveryToHouse* DeliveryToHouse::Instance()
{
  static DeliveryToHouse instance;

  return &instance;
}


void DeliveryToHouse::Enter(DeliveryMan* DeliveryMan)
{
  //if not already cooking put the stew in the oven
  if (!DeliveryMan->Delivery())
  {
    cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": Putting the stew in the oven";
  
    //send a delayed message myself so that I know when to take the stew
    //out of the oven
    Dispatch->DispatchMessage(1.5,                  //time delay
                              DeliveryMan->ID(),           //sender ID
                              DeliveryMan->ID(),           //receiver ID
                              Msg_DeliveryReady,        //msg
                              NO_ADDITIONAL_INFO); 

    DeliveryMan->SetDelivery(true);
  }
}


void DeliveryToHouse::Execute(DeliveryMan* DeliveryMan)
{
  cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": Time to delivery to Elsa";
}

void DeliveryToHouse::Exit(DeliveryMan* DeliveryMan)
{
  SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  
  cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": I should send a text saying, I'll be there in 5 minutes.";
}


bool DeliveryToHouse::OnMessage(DeliveryMan* DeliveryMan, const Telegram& msg)
{
  SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
    case Msg_DeliveryReady:
    {
      cout << "\nMessage received by " << GetNameOfEntity(DeliveryMan->ID()) <<
           " at time: " << Clock->GetCurrentTime();

      SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(DeliveryMan->ID()) << ": I'll go to delivery";

      //let hubby know the stew is ready
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                DeliveryMan->ID(),
                                ent_Elsa,
                                Msg_DeliveryReady,
                                NO_ADDITIONAL_INFO);

      DeliveryMan->SetDelivery(false);

      DeliveryMan->GetFSM()->ChangeState(ArrangeParcel::Instance());               
    }

    return true;

  }//end switch

  return false;
}