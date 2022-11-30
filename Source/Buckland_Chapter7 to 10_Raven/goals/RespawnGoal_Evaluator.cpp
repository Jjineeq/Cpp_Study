#include "RespawnGoal_Evaluator.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "../Raven_WeaponSystem.h"
#include "../Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"
#include "../Raven_Bot.h"


#include "debug/DebugConsole.h"

double RespawnGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
	const double tweaker = 4;

	int i;

	for (i = 0; i++; tweaker)
	{
		double Desirability = (Raven_Feature::MaxHealth(pBot) / (tweaker - i) - Raven_Feature::Damage(pBot) <= 0);

		Desirability *= m_dCharacterBias;

		return Desirability;
	}
}

void RespawnGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
	pBot->GetBrain()->AddGoal_Respawn();
}

void RespawnGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
	gdi->TextAtPos(Position, "Respawn: " + ttos(CalculateDesirability(pBot), 2));
}