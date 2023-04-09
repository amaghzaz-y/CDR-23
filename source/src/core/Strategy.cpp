#include "Strategy.h"

void Strategy::selectTeam(int number)
{
	if (number == 0)
	{
		team = 0;
	}
	else if (number == 1)
	{
		team = 1;
	}
}

void Strategy::calibrate()
{
	if (team == 0 && startingPosition == 0)
	{
		movement.setTargetRelative(PolarVec(180, 150).ToSteps());
		movement.runSync();
	}
}