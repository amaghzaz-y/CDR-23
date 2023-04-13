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
	pinMode(INIT_PIN, INPUT_PULLUP);
	pinMode(REED_PIN, INPUT_PULLUP);
	pinMode(TEAM_PIN, INPUT_PULLDOWN);
}
void Strategy::selectTeam(int number)
{
	team = number;
	Serial.print("TEAM SELECTED : ");
	Serial.println(team);
}

void Strategy::init()
{
	if (digitalRead(TEAM_PIN) == 1)
	{
		Serial.println("Starting Calibration");
		calibrate();
	}
	else
	{
		Serial.println("Waiting for init...");
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
	if (digitalRead(REED_PIN) == 0)
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
		movement.moveToRel(PolarVec(SIDE_B, 200).ToStepsCosSin());
		movement.runSync();
		movement.moveToRel(PolarVec(SIDE_CA, 115).ToStepsCosSin());
		movement.runSync();
		Steps rot = movement.rotateTo(SIDE_B);
		movement.moveToRel(rot);
		movement.runSync();
		movement.moveToRel(PolarVec(SIDE_BC, 200).ToStepsCosSin());
		movement.runSync();
		isHome = true;
		calibrated = true;
		currentPoint = Point2D(INITIAL_X, INITIAL_Y);
		delay(3000);
	}
	else if (team == 1)
	{
		movement.moveToRel(PolarVec(SIDE_C, 200).ToStepsCosSin());
		movement.runSync();
		movement.moveToRel(PolarVec(SIDE_AB, 115).ToStepsCosSin());
		movement.runSync();
		Steps rot = movement.rotateTo(SIDE_C);
		movement.moveToRel(rot);
		movement.runSync();
		movement.moveToRel(PolarVec(SIDE_BC, 200).ToStepsCosSin());
		movement.runSync();
		isHome = true;
		calibrated = true;
		currentPoint = Point2D(INITIAL_X, INITIAL_Y);
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
	isHome = false;
	calibrated = false;
	movement.moveToRel(nextPoint.toSteps());
	while (!movement.hasArrived())
	{
		if (isDetected)
		{
			movement.stop();
		}
		movement.run();
	}
	currentPoint = nextPoint;
}

void Strategy::setNextPoint(Point2D point)
{
	nextPoint = Point2D(point.X - currentPoint.X, point.Y - currentPoint.Y);
}

void Strategy::goHome() {}

void Strategy::start(bool lidar)
{
	isDetected = lidar;
	if (!isCalibrated())
	{
		calibrate();
	}
	while (currentInstruction < arrayLength)
	{
		setNextPoint(points[currentInstruction]);
		goToPoint();
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
		movement.moveToRel(vec.ToSteps());
		while (!movement.hasArrived())
		{
			if (isDetected)
			{
				movement.stop();
			}
			movement.run();
		}
		currentInstruction++;
	}
	goHome();
}