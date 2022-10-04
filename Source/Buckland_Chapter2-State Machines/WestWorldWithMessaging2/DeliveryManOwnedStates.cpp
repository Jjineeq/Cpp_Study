#include "DeliveryManOwnedStates.h"
#include "fsm/State.h"
#include "DeliveryMan.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
    static EnterMineAndDigForNugget instance;

    return &instance;
}


void EnterMineAndDigForNugget::Enter(DeliveryMan* pDeliveryMan)
{
    //if the DeliveryMan is not already located at the goldmine, he must
    //change location to the gold mine
    if (pDeliveryMan->Location() != goldmine)
    {
        cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Walkin' to the goldmine";

        pDeliveryMan->ChangeLocation(goldmine);
    }
}


void EnterMineAndDigForNugget::Execute(DeliveryMan* pDeliveryMan)
{
    //Now the DeliveryMan is at the goldmine he digs for gold until he
    //is carrying in excess of MaxNuggets. If he gets thirsty during
    //his digging he packs up work for a while and changes state to
    //gp to the saloon for a whiskey.
    pDeliveryMan->AddToGoldCarried(1);

    pDeliveryMan->IncreaseFatigue();

    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Pickin' up a nugget";

    //if enough gold mined, go and put it in the bank
    if (pDeliveryMan->PocketsFull())
    {
        pDeliveryMan->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
    }

    if (pDeliveryMan->Thirsty())
    {
        pDeliveryMan->GetFSM()->ChangeState(QuenchThirst::Instance());
    }
}


void EnterMineAndDigForNugget::Exit(DeliveryMan* pDeliveryMan)
{
    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": "
        << "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}


bool EnterMineAndDigForNugget::OnMessage(DeliveryMan* pDeliveryMan, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
    static VisitBankAndDepositGold instance;

    return &instance;
}

void VisitBankAndDepositGold::Enter(DeliveryMan* pDeliveryMan)
{
    //on entry the DeliveryMan makes sure he is located at the bank
    if (pDeliveryMan->Location() != bank)
    {
        cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Goin' to the bank. Yes siree";

        pDeliveryMan->ChangeLocation(bank);
    }
}


void VisitBankAndDepositGold::Execute(DeliveryMan* pDeliveryMan)
{
    //deposit the gold
    pDeliveryMan->AddToWealth(pDeliveryMan->GoldCarried());

    pDeliveryMan->SetGoldCarried(0);

    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": "
        << "Depositing gold. Total savings now: " << pDeliveryMan->Wealth();

    //wealthy enough to have a well earned rest?
    if (pDeliveryMan->Wealth() >= ComfortLevel)
    {
        cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": "
            << "WooHoo! Rich enough for now. Back home to mah li'lle lady";

        pDeliveryMan->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
    }

    //otherwise get more gold
    else
    {
        pDeliveryMan->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
    }
}


void VisitBankAndDepositGold::Exit(DeliveryMan* pDeliveryMan)
{
    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Leavin' the bank";
}


bool VisitBankAndDepositGold::OnMessage(DeliveryMan* pDeliveryMan, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
    static GoHomeAndSleepTilRested instance;

    return &instance;
}

void GoHomeAndSleepTilRested::Enter(DeliveryMan* pDeliveryMan)
{
    if (pDeliveryMan->Location() != shack)
    {
        cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Walkin' home";

        pDeliveryMan->ChangeLocation(shack);

        //let the wife know I'm home
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDeliveryMan->ID(),        //ID of sender
            ent_Elsa,            //ID of recipient
            Msg_HiHoneyImHome,   //the message
            NO_ADDITIONAL_INFO);
    }
}

void GoHomeAndSleepTilRested::Execute(DeliveryMan* pDeliveryMan)
{
    //if DeliveryMan is not fatigued start to dig for nuggets again.
    if (!pDeliveryMan->Fatigued())
    {
        cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": "
            << "All mah fatigue has drained away. Time to find more gold!";

        pDeliveryMan->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
    }

    else
    {
        //sleep
        pDeliveryMan->DecreaseFatigue();

        cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "ZZZZ... ";
    }
}

void GoHomeAndSleepTilRested::Exit(DeliveryMan* pDeliveryMan)
{
}


bool GoHomeAndSleepTilRested::OnMessage(DeliveryMan* pDeliveryMan, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_StewReady:

        cout << "\nMessage handled by " << GetNameOfEntity(pDeliveryMan->ID())
            << " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(pDeliveryMan->ID())
            << ": Okay Hun, ahm a comin'!";

        pDeliveryMan->GetFSM()->ChangeState(EatStew::Instance());

        return true;

    }//end switch

    return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
    static QuenchThirst instance;

    return &instance;
}

void QuenchThirst::Enter(DeliveryMan* pDeliveryMan)
{
    if (pDeliveryMan->Location() != saloon)
    {
        pDeliveryMan->ChangeLocation(saloon);

        cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
    }
}

void QuenchThirst::Execute(DeliveryMan* pDeliveryMan)
{
    pDeliveryMan->BuyAndDrinkAWhiskey();

    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "That's mighty fine sippin' liquer";

    pDeliveryMan->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
}


void QuenchThirst::Exit(DeliveryMan* pDeliveryMan)
{
    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Leaving the saloon, feelin' good";
}


bool QuenchThirst::OnMessage(DeliveryMan* pDeliveryMan, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
    static EatStew instance;

    return &instance;
}


void EatStew::Enter(DeliveryMan* pDeliveryMan)
{
    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Smells Reaaal goood Elsa!";
}

void EatStew::Execute(DeliveryMan* pDeliveryMan)
{
    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Tastes real good too!";

    pDeliveryMan->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(DeliveryMan* pDeliveryMan)
{
    cout << "\n" << GetNameOfEntity(pDeliveryMan->ID()) << ": " << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}


bool EatStew::OnMessage(DeliveryMan* pDeliveryMan, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}


