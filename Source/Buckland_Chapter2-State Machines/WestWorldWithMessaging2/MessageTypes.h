#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_DeliveryReady,
  Msg_BreakTime,
  Msg_GoAcademy,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_DeliveryReady:

      return "DeliveryReady";

  case Msg_BreakTime:

      return "BreakTime";

  case Msg_GoAcademy:

      return "GoAcademy";

  default:

    return "Not recognized!";
  }
}

#endif