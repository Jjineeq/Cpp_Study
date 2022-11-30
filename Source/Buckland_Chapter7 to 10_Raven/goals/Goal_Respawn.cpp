#include "Goal_Respawn.h"
#include "Goal_AttackTarget.h"
#include "../Raven_Bot.h"
#include "../Raven_Map.h"
#include "../Raven_Game.h"
#include "Raven_Feature.h"

void Goal_Respawn::Activate()
{
	m_iStatus = active;

	RemoveAllSubgoals();
	
	int i;

	m_imaxcount = 4;

	for(i = 0; i++;)
	{
		m_vPoint = m_pOwner->GetWorld()->GetMap()->GetRandomSpawnPoint();

		m_pOwner->Spawn(m_vPoint);

		m_pOwner->SetAlive();

		m_iMaxHealth = m_pOwner->MaxHealth();

		m_pOwner->ReduceHealth(m_iMaxHealth*(1 / (m_imaxcount - i)));

		if (i == m_imaxcount)
		{
			m_pOwner->SetDead();
			break;
		}
	}

	if (m_pOwner->isAlive())
	{
		AddSubgoal(new Goal_AttackTarget(m_pOwner));
	}
}

int Goal_Respawn::Process()
{
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	return m_iStatus;
}
