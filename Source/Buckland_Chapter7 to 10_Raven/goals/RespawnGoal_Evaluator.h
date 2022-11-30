#ifndef RAVEN_RESPAWN_GOAL_EVALUATOR
#define RAVEN_RESPAWN_GOAL_EVALUATOR
#pragma warning (disable:4786)

#include "Goal_Evaluator.h"
#include "../Raven_Bot.h"

class RespawnGoal_Evaluator : public Goal_Evaluator
{
public:

	RespawnGoal_Evaluator(double bias) :Goal_Evaluator(bias) {}

	double CalculateDesirability(Raven_Bot* pBot);

	void SetGoal(Raven_Bot* pEnt);

	void RenderInfo(Vector2D Position, Raven_Bot* pBot);
};
#endif