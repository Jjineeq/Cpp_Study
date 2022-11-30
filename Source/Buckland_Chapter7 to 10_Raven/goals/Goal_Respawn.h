#ifndef GOAL_RESPAWN_H
#define GOAL_RESPAWN_H
#pragma warning (disable:4786)

#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"

class Goal_Respawn : public Goal_Composite<Raven_Bot>
{
private:

	Vector2D m_vPoint;

	int m_iMaxHealth;

	int m_imaxcount;

public:

	Goal_Respawn(Raven_Bot* pOwner) :Goal_Composite<Raven_Bot>(pOwner, goal_respawn)
	{}

	void Activate();

	int Process();

	void Terminate() { m_iStatus = completed; }

};
#endif