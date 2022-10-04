#include "MinersManager.h"

bool MinersManager::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void MinersManager::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}