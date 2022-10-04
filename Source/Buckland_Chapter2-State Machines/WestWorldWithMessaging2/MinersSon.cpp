#include "MinersSon.h"

bool MinersSon::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void MinersSon::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}