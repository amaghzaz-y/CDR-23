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

void Strategy::selectHome(int number)
{
	home = number;
}

void Strategy::calibrate()
{
	if (team == 0 && home == 0)
	{
		movement.setTargetRelative(PolarVec(180, 150).ToSteps());
		movement.runSync();
		movement.setTargetRelative(PolarVec(270, 150).ToSteps());
		movement.runSync();
		isHome = true;
		calibrated = true;
	}
	else if (team == 1 && home == 0)
	{
		movement.setTargetRelative(PolarVec(180, 150).ToSteps());
		movement.runSync();
		movement.setTargetRelative(PolarVec(270, 150).ToSteps());
		movement.runSync();
		isHome = true;
		calibrated = true;
	}
}

bool Strategy::isCalibrated()
{
	return calibrated;
}

bool Strategy::atHome()
{
	return isHome;
}

void Strategy::stop()
{
	movement.fullStop();
}

void Strategy::setTable(Point2D *p, int len)
{
	points = p;
	arrayLength = len;
}

void Strategy::execute()
{
	movement.setTargetRelative(currentPoint.toSteps());
	while (!movement.hasArrived())
	{
		if (lidar.hasDetected())
		{
			movement.stop();
		}
		movement.run();
	}
}

void Strategy::start()
{
	while (currentInstruction < arrayLength)
	{
		currentPoint = points[currentInstruction];
		execute();
		currentInstruction++;
	}
}