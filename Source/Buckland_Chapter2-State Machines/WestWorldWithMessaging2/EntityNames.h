#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Miner_Bob,

  ent_Elsa,

  ent_Kris,

  ent_Liam,

  ent_Noah
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:
    
    return "Elsa";

  case ent_Kris:

      return "Kris";
  
  case ent_Liam:

      return "Liam";

  case ent_Noah:

      return "Noah";

  default:

    return "UNKNOWN!";
  }
}

#endif