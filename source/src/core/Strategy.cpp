#include "Strategy.h"

Strategy::Strategy()
{
	currentInstruction = 0;
	arrayLength = 0;
	isPulled = false;
	calibrated = false;
	isHome = false;
	isDetected = false;
	team = 0;
	home = 0;
}

void Strategy::setup()
{
	movement.setup();
}
void Strategy::selectTeam(int number)
{
	team = number;
	Serial.print("TEAM SELECTED : ");
	Serial.println(team);
}

void Strategy::init()
{
	if (digitalRead(INIT_PIN) == 1)
	{
		Serial.println("Starting Init");
		calibrate();
		while (isReady())
			;
	}
	else
	{
		while (1)
			;
	}
}

void Strategy::makeSelection()
{
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
	{
		Serial.println("not ready");
		return false;
	}
	Serial.println("ready");
	return true;
}

void Strategy::calibrate()
{
	if (team == 0)
	{
		movement.setTargetRelative(PolarVec(SIDE_B, 200).ToStepsCosSin());
		movement.runSync();
		movement.setTargetRelative(PolarVec(SIDE_CA, 115).ToStepsCosSin());
		movement.runSync();
		Steps rot = movement.rotateTo(SIDE_B);
		movement.setTargetRelative(rot);
		movement.runSync();
		movement.setTargetRelative(PolarVec(SIDE_BC, 200).ToStepsCosSin());
		movement.runSync();
		isHome = true;
		calibrated = true;
		delay(3000);
	}
	else if (team == 1)
	{
		movement.setTargetRelative(PolarVec(SIDE_C, 200).ToStepsCosSin());
		movement.runSync();
		movement.setTargetRelative(PolarVec(SIDE_AB, 115).ToStepsCosSin());
		movement.runSync();
		Steps rot = movement.rotateTo(SIDE_C);
		movement.setTargetRelative(rot);
		movement.runSync();
		movement.setTargetRelative(PolarVec(SIDE_BC, 200).ToStepsCosSin());
		movement.runSync();
		isHome = true;
		calibrated = true;
		delay(3000);
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
	if (!isCalibrated())
	{
		calibrate();
	}
	while (currentInstruction < arrayLength)
	{
		currentPoint = points[currentInstruction];
		goToPoint();
		updatePOS(currentPoint);
		currentInstruction++;
	}
	goHome();
}

void Strategy::executeVecs(bool lidar)
{
	isDetected = lidar;
	if (!isCalibrated())
	{
		calibrate();
	}
	while (currentInstruction < arrayLength)
	{
		PolarVec vec = vecs[currentInstruction];
		movement.setTargetRelative(vec.ToSteps());
		while (!movement.hasArrived())
		{
			if (isDetected)
			{
				movement.stop();
			}
			movement.run();
		}
		// updatePOS(currentPoint);
		currentInstruction++;
	}
	goHome();
}