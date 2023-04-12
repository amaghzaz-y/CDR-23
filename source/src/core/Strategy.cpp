#include "Strategy.h"

Strategy::Strategy()
{
}

void Strategy::selectTeam(int number)
{
	team = number;
}

void Strategy::selectHome(int number)
{
	home = number;
}

void Strategy::makeSelection()
{
	if (digitalRead(HOME_PIN) == 0)
	{
		selectHome(0);
	}
	else
	{
		selectHome(1);
	}

	if (digitalRead(TEAM_PIN) == 0)
	{
		selectTeam(0);
	}
	else
	{
		selectTeam(1);
	}
}

bool Strategy::isReady()
{
	if (digitalRead(PIN_REED) == 0)
		return false;
	return true;
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

void Strategy::setPoints(Point2D *p, int len)
{
	points = p;
	arrayLength = len;
}

void Strategy::setVecs(PolarVec *v, int len)
{
	vecs = v;
	arrayLength = len;
}

void Strategy::goToPoint()
{
	movement.setTargetRelative(currentPoint.toSteps());
	while (!movement.hasArrived())
	{
		if (isDetected)
		{
			movement.stop();
		}
		movement.run();
	}
}
void Strategy::goHome() {}

void Strategy::updatePOS(Point2D point)
{
	currentPoint = point;
}

void Strategy::start(bool lidar)
{
	isDetected = lidar;
	while (currentInstruction < arrayLength)
	{
		currentPoint = points[currentInstruction];
		goToPoint();
		updatePOS(currentPoint);
		currentInstruction++;
	}
	goHome();
}

void Strategy::executeVecs()
{
	while (currentInstruction < arrayLength)
	{
		Vec2 vec = vecs[currentInstruction].ToPoint2D();
		currentPoint = Point2D(vec.A, vec.B);
		goToPoint();
		updatePOS(currentPoint);
		currentInstruction++;
	}
	goHome();
}