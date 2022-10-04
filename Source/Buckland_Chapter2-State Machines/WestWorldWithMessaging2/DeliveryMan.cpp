#include "DeliveryMan.h"

bool DeliveryMan::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void DeliveryMan::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}