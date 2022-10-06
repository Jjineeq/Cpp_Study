#include <fstream>
#include <time.h>
#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "MinersSon.h"
#include "MinersManager.h"
#include "DeliveryMan.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;
using namespace std;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //create his son
  MinersSon* Kris = new MinersSon(ent_Kris);

  //create deliver
  DeliveryMan* Liam = new DeliveryMan(ent_Liam);

  //create Manager
  MinersManager* Noah = new MinersManager(ent_Noah);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Kris);
  EntityMgr->RegisterEntity(Liam);
  EntityMgr->RegisterEntity(Noah);


  //run Bob and Elsa through a few Update calls
  for (int i=0; i<20; ++i)
  { 
    Bob->Update();
    Elsa->Update();
    Kris->Update();
    Liam->Update();
    Noah->Update();

    //dispatch any delayed messages 
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete Kris;
  delete Liam;
  delete Noah;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();
  printf("2018312031 Jang_seong_ho");

  return 0;
}






